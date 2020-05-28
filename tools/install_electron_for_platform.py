# -*- coding: utf-8 -*-
import subprocess
import os
import glob
import sys
import shutil
import re
import errno
from subprocess import call

def make_dir_exist(path):
    if not os.path.exists(path):
        try:
            os.makedirs(path)
        except OSError as exc: # Guard against race condition
            if exc.errno != errno.EEXIST:
                raise

def cp_files(from_Path, to_path, ext):
    from_Path = os.path.join(from_Path, ext)
    files = glob.iglob(from_Path)
    make_dir_exist(to_path)
    for file in files:
        if os.path.isfile(file):
            shutil.copy2(file, to_path)

def cp_one_file(from_Path, to_path):
    make_dir_exist(os.path.dirname(to_path))
    if os.path.isfile(from_Path):
        shutil.copy2(from_Path, to_path)

def main():
    # 直接在当前目录下查找electron的压缩包，从中得出对应版本号，并根据命令行参数指定的下载URL构造缓存目录的名称
    if len(sys.argv) < 2:
        print("need cmdline params: \"target_arch, download_url\"")
        exit(1)

    # 要安装的目标electron架构
    target_arch = sys.argv[1]
    print ("dst target_arch: %s" % target_arch)

    # 从哪个URL下载，不传参就从github下
    url = "https://github.com/electron/electron/releases/download/"
    #url = "https://npm.taobao.org/mirrors/electron/"
    if len(sys.argv) >= 3:
        url = sys.argv[2]
    print ("dst download url: %s" % url)

    # 遍历当前目录，查找符合electron压缩包命名规则的文件，从中提取版本号"electron-v9.0.0-win32-ia32.zip"
    # 只取一个版本文件，如果目录下存在多个，则不执行安装操作
    ver_list = []
    file_list = []
    hash_file_name = "SHASUMS256.txt"
    is_hash_file_exists = False
    pattern_str = "electron-v(\d.\d.\d)-" + sys.platform + "-" + target_arch + ".zip"
    pattern = re.compile(pattern_str, re.I)
    for root, dirs, files in os.walk(os.path.dirname(__file__)):
        for name in files:
            if name == hash_file_name:
                is_hash_file_exists = True

            m = pattern.match(name)
            if m:
                ver_list.append(m.group(1))
                file_list.append(name)

    if len(file_list) == 0:
        print("can't find electron release file!")
        exit(1)
    elif len(file_list) > 1:
        print("find more than one electron release file!")
        print (file_list)
        exit(1)
    if is_hash_file_exists == False:
        print("can't find electron hash file!")
        exit(1)

    # 确定了版本文件和版本号
    file_name = file_list[0]
    elec_ver = ver_list[0]
    print("find electron release file \"%s\"" % file_name)
    
    # 构造缓存目录名称并创建
    url = url.replace("://", "").replace("/", "")
    cache_release_dir_name = url + 'v' + elec_ver + file_name
    cache_hash_dir_name = url + 'v' + elec_ver + hash_file_name

    # windows下放置到“%localappdata%\electron\Cache”中，
    # mac下放置到“~/Library/Caches/electron”中
    if sys.platform == 'win32':
        sys_dir = os.getenv('LOCALAPPDATA')
        sys_dir = os.path.join(sys_dir, "electron\Cache")
    elif sys.platform == 'darwin':
        sys_dir = os.path.expanduser("~/Library/Caches/electron")

    # copy
    cache_release_path = os.path.join(sys_dir, cache_release_dir_name, file_name)
    cache_hash_path = os.path.join(sys_dir, cache_hash_dir_name, hash_file_name)

    release_path = os.path.join(os.path.dirname(__file__), file_name)
    hash_path = os.path.join(os.path.dirname(__file__), hash_file_name)

    cp_one_file(release_path, cache_release_path)
    print("successfully copy to %s" % cache_release_path)
    cp_one_file(hash_path, cache_hash_path)
    print("successfully copy to %s" % cache_hash_path)

    # 执行npm install命令
    # npm install electron@9.0.0 --platform=win32 --arch=ia32 --save-dev --verbose
    os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    cmd = "npm install electron@{} --platform={} --arch={} --save-dev --verbose".format(elec_ver, sys.platform, target_arch)
    print("execute npm install command...\n\t\"%s\"" % cmd)
    os.system(cmd)
    print("npm install command execute completed.")

if __name__ == '__main__':
    main()