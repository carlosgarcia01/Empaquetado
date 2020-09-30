const cluster = require("cluster");
const http = require("http");
const addon = require("../../build/Release/addon");
//const numCPUs = require('os').cpus().length;

const obj = new addon.usbdevWrap(10);

if (cluster.isMaster) {
  console.log(`Master ${process.pid} is running`);

  //   // Fork workers.
  //   for (let i = 0; i < 1; i++) {
  //     cluster.fork();
  //   }

  cluster.fork();
  cluster.on("fork", (worker) => {
    console.log("hilo fork");
    //obj.MainWrap();
    console.log('creo el MainWrap*************************************');
  });

  cluster.on("exit", (worker, code, signal) => {
    console.log(`worker ${worker.process.pid} died`);
  });
} else {
  // Workers can share any TCP connection
  // In this case it is an HTTP server
  http
    .createServer((req, res) => {
      res.writeHead(200);

      res.end("Server is created");
    })
    .listen(8000);

    console.log(obj.plusOneWrap());
    console.log(obj.plusOneWrap());
    //console.log(obj.openDeviceWrap());
    console.log(obj.serviceSlotWrap());
    console.log(obj.plusOneWrap());
    console.log(obj.plusOneWrap());
    console.log("proceso los que necesitamos\\\\\\");
    console.log(`Worker ${process.pid} started`);
  console.log(`Worker ${process.pid} started`);
}
