const obj = require('./usbdev');

//const dotenv = require('dotenv').config();
// here would one initialize this child
// this will be executed only once
console.log('[Child]', 'initalize');

// // here one listens for new tasks from the parent
process.on('message', function(parentData) {
    //do some intense work here
    // console.log('[Child]', 'Child doing some intense work');
    if(parentData == 'Exec') process.send(`PlusOne: ${obj.MainWrap()}`);
    else process.send('what????????????');
    
})

// let data = process.argv[2];

// const objWrap = (obj) =>{
//     console.log('Data od obj: ',obj);
// }

// objWrap(data);