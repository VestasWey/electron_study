const { app, BrowserWindow, Menu, MenuItem, dialog, shell, nativeImage } = require('electron')
const ffi = require('ffi-napi')
const path = require('path');

const bin_dir = path.join(process.cwd(), 'bin')
const cwd_dir = path.dirname(__dirname)

console.log(require.resolve('electron'));

let study_main_lib
let fn_set_pchar_callback1
try {
  study_main_lib = new ffi.Library(path.join(bin_dir, 'ffapi_study'),
    {
      'fn_add': ['int', ['int', 'int']],

      'fn_set_pchar_callback1': ['void', ['string']],
      'fn_set_pchar_callback2': ['void', ['string']],
      'fn_set_pchar_callback3': ['void', ['string']],
    })
} catch (error) {
  console.log(`ffi.Library err: ` + error);
}

function init_native_libs(){
  fn_set_pchar_callback1 = ffi.Callback('void', ['string'], (str)=>{
    console.log('ffi.fn_set_pchar_callback1: ' + str);
  })
  if(study_main_lib)
  {
    study_main_lib.fn_set_pchar_callback1(fn_set_pchar_callback1)
    //study_main_lib.fn_set_pchar_callback2(fn_set_pchar_callback2)
    //study_main_lib.fn_set_pchar_callback3(fn_set_pchar_callback3)
  }
}

function createWindow() {

  // 创建浏览器窗口
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      nodeIntegration: true
    }
  })

  // 并且为你的应用加载index.html
  win.loadFile(path.join(cwd_dir, 'html/index.html'))

  // 修改默认顶层菜单的响应
  let am = Menu.getApplicationMenu()
  if (am) {
    let hm = am.items[4] // Help
    if (hm) {
      let shm = hm.submenu.items[0] // 'Learn More'
      if (shm) {
        shm.click = () => {
          dialog.showMessageBox({
            type: "info",//图标类型
            title: "帮助",//信息提示框标题
            message: "顶层菜单子项响应",//信息提示框内容
            buttons: ["确认", "取消"],//下方显示的按钮
            //icon:nativeImage.createFromPath("./icon/search-globe.png"),//图标
            cancelId: 2//点击x号关闭返回值
          }).then((mb_ret) => {
            if (mb_ret.response === 0) {
              shell.openExternal('https://www.baidu.com/')
            }
          })
        }
      }
    }
  }

  // 页面右键菜单
  const context_menu = new Menu;
  context_menu.append(new MenuItem({
    label: 'first',
    click: (menuItem, browserWindow, event) => {
      //dialog.showOpenDialog(win)
      dialog.showErrorBox('title', 'bin_dir:' + bin_dir + '\ncwd_dir: ' +  cwd_dir)
    }
  }))
  context_menu.append(new MenuItem({ type: 'separator' }))
  context_menu.append(new MenuItem({
    label: 'second',
    type: 'checkbox',
    checked: true,
    click: (menuItem, browserWindow, event) => {
      //dialog.showSaveDialog(win)
      
      if (study_main_lib) {    
        let ret = study_main_lib.fn_add(12312, 423423)
        dialog.showErrorBox('title', `the result of fn_add is: ` + ret)
      }
    }
  }))
  // 设置右键菜单
  win.webContents.on('context-menu', (event, params) => {
    context_menu.popup(win, params.x, params.y)
  })

  // 打开开发者工具
  //win.webContents.openDevTools()
}

function initApp() {
  init_native_libs()
  createWindow()
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// 部分 API 在 ready 事件触发后才能使用。
app.whenReady().then(initApp)

// Quit when all windows are closed.
app.on('window-all-closed', () => {
  // 在 macOS 上，除非用户用 Cmd + Q 确定地退出，
  // 否则绝大部分应用及其菜单栏会保持激活。
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  // 在macOS上，当单击dock图标并且没有其他窗口打开时，
  // 通常在应用程序中重新创建一个窗口。
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow()
  }
})

app.on('browser-window-created', (event, window) => {
  /* window.webContents.on('context-menu', (event, params)=>{
    g_conteext_menu.popup(window, params.x, params.y)
  }) */
})

// In this file you can include the rest of your app's specific main process
// code. 也可以拆分成几个文件，然后用 require 导入。
process.on('beforeExit', () => {
  if(study_main_lib)
  {
  }
})

process.on('exit', () => {
  fn_set_pchar_callback1 = null
})