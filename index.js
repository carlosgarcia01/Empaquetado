// const addon = require('./build/Release/addon');

// const obj = new addon.usbdevWrap(10);

// console.log("Entrando en index.js")

// obj.MainWrap();
const { exec } = require('child_process');
const path = require('path');
const obj = require('./src/promesa');

const pathPromise = path.join(__dirname,'/src/promesa.js');


console.log('Hello before')

exec(`sudo node ${pathPromise}&`);

console.log('Hello world after')

console.log(obj.plusOneWrap());
console.log(obj.plusOneWrap());
console.log(obj.plusOneWrap());
console.log(obj.plusOneWrap());
console.log(obj.plusOneWrap());
console.log(obj.plusOneWrap());

console.log(obj.openDeviceWrap());
console.log(obj.serviceSlotWrap()); 

//obj.execWrap();

/*const obj2 = new addon.videostreamingWrap(20);

console.log(obj2.plusOne());
console.log(obj2.serviceSlotWrap());*/

