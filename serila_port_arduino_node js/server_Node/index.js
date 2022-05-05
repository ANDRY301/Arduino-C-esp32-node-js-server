
// npm i express cors serialport mysql body-parser  

const express = require("express");

const app = express();
const cors = require("cors");
const SerialPort = require('serialport');
const mysql      = require('mysql')
const bodyParser = require('body-parser') ;

const db = mysql.createConnection({
  host     :"...",
  user     :"..",
  password :"..",
  database :"..."
})


app.use(bodyParser.urlencoded({extended:true}))
app.use(cors());
app.use(express.json());

 app.listen("3001", () => {
  console.log("Server Running on Port 3001...");
});



const ReadLine = SerialPort.parsers.Readline;
const port = new SerialPort("COM4", {
  baudRate: 115200
});
const parser = port.pipe(new ReadLine({ delimiter: '\r\n' }));


  parser.on('data', function (data) {
  console.log(data)
    let temp = [parseInt(data) ]
      

        const deka = "INSERT INTO esp32num1 (result) VALUES (?)"     
        db.query(deka,temp,(err,result)=>{ 
          console.log("ok bien envoyer le izy")
        })

        const Upsql = "UPDATE esp32num1set  SET result =?  WHERE  id=1  ";
      
        db.query(Upsql,temp,(err,result)=>{ 
          console.log("ok bien set le")
        })

       });



