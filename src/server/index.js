const cluster = require('cluster');
const app = require("./server");

const addon = require("../../build/Release/addon");

const obj = new addon.usbdevWrap(10);

app.use("/obj", (req, res) => {
 // mainWrap()
  res.json({ res: "Ejecutando....." });
  //obj.MainWrap()
//   console.log(obj.plusOneWrap());
//   console.log(obj.plusOneWrap());
//   //console.log(obj.openDeviceWrap());
//   console.log(obj.serviceSlotWrap());

});

app.listen(app.get("port"), () => {
  console.log(`server on localhost:${app.get("port")}`);
  //obj.MainWrap();
});


const mainWrap = () =>{


function errorMsg() {
  console.error('Something must be wrong with the connection ...');
}

  if (cluster.isMaster) {
    /// console.log(`Master ${process.pid} is running`);  // Fork workers.
      //console.log("creacion de hijo");
      cluster.fork();
      cluster.on('fork', (worker) => {
        //console.log("hilo fork");
        obj.MainWrap();
        //console.log('creo el MainWrap*************************************');
      });
      cluster.on('exit', (worker, code, signal) => {
      //console.log(`worker ${worker.process.pid} died`);
    });
  } else {
  // console.log("hilos hijos");
      console.log(obj.plusOneWrap());
      console.log(obj.plusOneWrap());
    //console.log(obj.openDeviceWrap());
      console.log(obj.serviceSlotWrap());
      console.log(obj.plusOneWrap());
      console.log(obj.plusOneWrap());
      console.log('proceso que necesitamos\\\\\\');
      console.log(`Worker ${process.pid} started`);
  }

}