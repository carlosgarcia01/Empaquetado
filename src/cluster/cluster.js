const cluster = require('cluster');
const addon = require('../../build/Release/addon');

const obj = new addon.usbdevWrap(10);

obj.MainWrap();

setInterval(() => {
  console.log('entraa**********************');
  obj.processEvents();
}, 300);
obj.serviceSlotWrap();
setTimeout(()=>{
  console.log('Ingresa al time****************************************************');
  kill()
},5000)

function kill() {
  console.log("serviceslotoff: ", obj.serviceSlotWrapOff());
}

// function secondCluster() {
//   console.log("Entrando en cluster secundario");
//   //obj.setupWrap();
    console.log(obj.plusOneWrap());
    console.log(obj.plusOneWrap());
   console.log(obj.plusOneWrap());
  
//   console.log("serviceSlotOut: ",obj.serviceSlotWrap());
//   kill();
// }


// if (cluster.isMaster) {
//   console.log(`Master ${process.pid} is running`);  // Fork workers.

//   cluster.fork();
//   cluster.on('fork', (worker) => {
//     obj.MainWrap();
//   });

// } else {
//   setTimeout(secondCluster, 3000);
// }
