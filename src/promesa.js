const addon = require('../build/Release/addon');

const obj = new addon.usbdevWrap(10);

console.log("Entrando en index.js")



const promesa = () =>{
    return new Promise((resolve,reject)=>{
        // if(true){
        //     ciclo();
        //     resolve();
        // }
        // else{
        //     reject('hubo un problema');
        // }
        resolve(obj.MainWrap())
        reject('Problema');
    })
}

const ciclo = () => {
    let i = 0;
   while(true){
        obj.MainWrap();
   }
}

const main = async() => promesa();

main();

module.exports = obj;