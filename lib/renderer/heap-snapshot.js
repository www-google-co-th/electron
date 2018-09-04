const { ipcRenderer } = require('electron')
const errorUtils = require('../common/error-utils')

module.exports = (process) => {
  ipcRenderer.on('ELECTRON_RENDERER_TAKE_HEAP_SNAPSHOT', (event, requestId, args) => {
    new Promise(resolve => {
      resolve(process.takeHeapSnapshot(...args))
    }).then(result => {
      return [null, result]
    }, error => {
      return [errorUtils.serialize(error)]
    }).then(responseArgs => {
      event.sender.send(`ELECTRON_BROWSER_TAKE_HEAP_SNAPSHOT_RESULT_${requestId}`, ...responseArgs)
    })
  })
}
