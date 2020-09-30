const express = require('express');
require('dotenv').config();
const app = express();
const morgan = require('morgan');


app.set('port',process.env.PORT || 3050);


app.use(morgan('dev'));
app.use(express.urlencoded({extended:false}));
app.use(express.json());


module.exports = app;