// const addon = require('./build/Release/addon');

// const obj = new addon.usbdevWrap(10);

// console.log("Entrando en index.js")

// // obj.MainWrap();
// const { exec } = require('child_process');
// const path = require('path');
// // const obj = require('./src/promesa');
// const app = require('./src/server');


// const addon = require('./build/Release/addon');

// const main = require('./src/mainWrap');

// const obj = new addon.usbdevWrap(10);



// const pathWrap = path.join(__dirname,'/src/mainWrap.js');

// console.log(pathWrap)
// //Tener en cuenta forever stopall
// exec(`forever start ${pathWrap}`);

// console.log(obj.plusOneWrap());
// console.log(obj.plusOneWrap());
// console.log(obj.plusOneWrap());
// console.log(obj.plusOneWrap());
// console.log(obj.plusOneWrap());
// console.log(obj.plusOneWrap());

// console.log(obj.openDeviceWrap());
// console.log(obj.serviceSlotWrap()); 

//console.log("Entrando en index.js")

// app.use('/obj',(req,res)=>{
//     res.json({res:"Ejecutando....."})
//     //exec(`sudo node ${pathPromise}&`);

//     console.log('Hello world after')
//     console.log(obj.plusOneWrap());
//     console.log(obj.plusOneWrap());
//     console.log(obj.plusOneWrap());
//     console.log(obj.plusOneWrap());
//     console.log(obj.plusOneWrap());
//     console.log(obj.plusOneWrap());

//     console.log(obj.openDeviceWrap());
//     console.log(obj.serviceSlotWrap()); 
// })



// app.listen(app.get('port'), () => {
//     console.log(`server on localhost:${app.get('port')}`)
// })

//obj.MainWrap()

// //exec(`sudo node ${pathPromise}&`);

// console.log('Hello world after')

// console.log(obj.plusOneWrap());
// console.log(obj.plusOneWrap());
// console.log(obj.plusOneWrap());
// console.log(obj.plusOneWrap());
// console.log(obj.plusOneWrap());
// console.log(obj.plusOneWrap());

// console.log(obj.openDeviceWrap());
// console.log(obj.serviceSlotWrap()); 

//obj.execWrap();

/*const obj2 = new addon.videostreamingWrap(20);

console.log(obj2.plusOne());
console.log(obj2.serviceSlotWrap());*/

// obj.MainWrap();

const addon = require('./build/Release/addon');
const init = require('./obj.js')


console.log("Entramos en index******************************");

initObject();//obj.MainWrap();

console.log('sale de la funcion******************************');


//console.log(obj.serviceSlotWrap()); 
function otroProcess(obj){
    // const obj = new addon.usbdevWrap(10);
    console.log(obj.plusOneWrap());
    console.log(obj.plusOneWrap());
    console.log(obj.plusOneWrap());
    console.log(obj.plusOneWrap());
    console.log(obj.plusOneWrap());
    console.log(obj.plusOneWrap());
    console.log(obj.openDeviceWrap());
}

function initObject (){
    const obj = new addon.usbdevWrap(10);
    console.log("promesa",obj)
    try{
        return new Promise((resolve, reject) =>{ 
            console.log("ejecucion MainWrap()")                
                obj.MainWrap();
                otroProcess(obj);
            resolve(true);
        })
    }catch(err){
        console.log('ERRORRRRR' ,err);
    }
}