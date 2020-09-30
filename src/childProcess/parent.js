const child_process = require('child_process');
const obj = require('./usbdev');
//const obj = new addon.usbdevWrap(10);

//process.obj = new addon.usbdevWrap(10);

console.log('[Parent]', 'initalize');

// const child1 = child_process.fork(__dirname + '/child');
// child1.on('message', function(data) { 
//     console.log('[Parent]', 'Answer from child: ', data); 
// });

// const child1 = child_process.fork('child.js',obj,{cwd:"./src/childProcess"});


// child1.on('message', function(data) { 
//     console.log('[Parent]', 'Answer from child: ', data); 
// });
console.log(obj.serviceSlotWrap());
//console.log("Obj en parent: ",obj.plusOneWrap());
//child1.send("Exec"); // Hello to you too :)

console.log(obj.plusOneWrap());
console.log(obj.plusOneWrap());
//console.log(obj.openDeviceWrap());
//console.log(obj.serviceSlotWrap());

// child1.on('exit',()=>console.log('child terminated'))

// child1.send(obj); // Hello to you too :)
// child1.send(obj); // Hello to you too :)

// one can send as many messages as one want
//child1.send("Hello"); // Hello to you too :)
//child1.send("Hello"); // Hello to you too :)

// one can also have multiple children
// var child2 = child_process.fork(__dirname + '/child');

// child2.on('message', function(msg) { 
//     console.log('[Parent]', 'Answer from child: ', msg); 
// });


// child2.send("Bye");
// child2.send("Bye")
