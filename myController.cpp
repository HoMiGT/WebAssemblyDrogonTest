#include "myController.h"
#include <fstream>

using namespace std;
using namespace drogon;


static const string html0 = R"(<!doctype html>
<html>
   <head>
      <meta charset="utf-8">
      <title>WebAssembly Add Function</title>
      <style>
         div {
            font-size : 30px; text-align : center; color:orange;
         }
      </style>
   </head>
   <body>
      <div id="textcontent"></div>
      <script>
         fetch("/0/wasm")
         .then(bytes => bytes.arrayBuffer())
         .then(mod => WebAssembly.compile(mod))
         .then(module => {return new WebAssembly.Instance(module)})
         .then(instance => {
            console.log(instance);
            let buffer = new Uint8Array(instance.exports.memory.buffer);
            let test = instance.exports.c_hello();
            let mytext = "";
            for (let i=test; buffer[i]; i++) {
               mytext += String.fromCharCode(buffer[i]);
            }
            console.log(mytext); document.getElementById("textcontent").innerHTML = mytext;
         });
      </script>
   </body>
</html>)";

static const string file0 = R"(D:\Projects\cxx\ws1\t.wasm)";

AddFunction(CHelloWorld, 0, html0, file0)

static const string html1 = R"(<!doctype html>
<html>
   <head>
      <meta charset="utf-8">
      <title>WebAssembly Add Function</title>
      <style>
         div {
            font-size : 30px; text-align : center; color:orange;
         }
      </style>
   </head>
   <body>
      <div id="textcontent"></div>
      <script>
         let factorial;
         fetch("/1/wasm")
         .then(bytes => bytes.arrayBuffer())
         .then(mod => WebAssembly.compile(mod))
         .then(module => {return new WebAssembly.Instance(module)})
         .then(instance => {
            factorial = instance.exports._Z4facti;
            console.log("Test on Console by use factorial");
         });
      </script>
   </body>
</html>)";

static const string file1 = R"(D:\Downloads\test (4).wasm)";

AddFunction(CModule, 1, html1, file1)


static const string html2 = R"(<!DOCTYPE html> 
<html>
   <head>
      <meta charset="UTF-8">
   </head>
   <body>
      <script>
         var wasmMemory = new WebAssembly.Memory({'initial': 256,'maximum': 65536}); 
         const importObj = { env:{} };
         fetch("/2/wasm") .then(bytes => bytes.arrayBuffer()) .then(
            module => WebAssembly.instantiate(module, importObj)
         )
         .then(finalcode => {        
            console.log(finalcode);     
            console.log(WebAssembly.Module.imports(finalcode.module)); 
            console.log(finalcode.instance.exports.t1());    
            console.log(finalcode.instance.exports.t2());   
            console.log(finalcode.instance.exports.main()); 
         });
      </script>
   </body>
</html>)";

static const string file2 = R"(D:\Projects\cxx\WebAssembly\ws1\maintest.wasm)";

AddFunction(CTestMain, 2, html2, file2)

static const string html3 = R"(<!DOCTYPE html> 
<html>
   <head>
      <meta charset="UTF-8">
   </head>
   <body>
      <script>
         const importObj = {
              module: {}
           }; 
           fetch("/3/wasm")      
              .then(bytes => bytes.arrayBuffer())          
              .then(module => WebAssembly.instantiate(module,importObj))                 
              .then(finalcode => {
         
              console.log(finalcode); console.log(finalcode.instance.exports.square(25)); 
           });
      </script>
   </body>
</html>)";

static const string file3 = R"(D:\Projects\cxx\WebAssembly\ws2\square.wasm)";

AddFunction(CSquare, 3, html3, file3)


static const string html4 = R"(<!doctype html> 
<html>
   <head> 
      <meta charset="utf-8">
      <title>WebAssembly Reverse Number</title>
      <style>
         div { 
            font-size : 30px; text-align : center; color:orange; 
         } 
      </style>
   </head>
   <body>
      <div id="textcontent"></div>
      <script> 
         let reverse; 
         fetch("/4/wasm")  
            .then(bytes => bytes.arrayBuffer()) 
            .then(mod => WebAssembly.compile(mod)) 
            .then(module => {return new WebAssembly.Instance(module) })
            .then(instance => { 
            console.log(instance); 
            reverse = instance.exports._Z13reversenumberi(1439898); 
            console.log("The reverse of 1439898 = " +reverse); 
            document.getElementById("textcontent")
               .innerHTML = "The reverse of 1439898 = " +reverse; 
         }); 
      </script>
   </body>
</html>)";

static const string file4 = R"(D:\Projects\cxx\WebAssembly\ws3\reverse.wasm)";

AddFunction(CReverse, 4, html4, file4)


static const string html5 = R"(<!DOCTYPE html> 
<html>
   <head> 
      <meta charset="UTF-8">
   </head>
   <body>
      <script> 
         const importObj = { 
            env: { _Z10displaylogi: n => console.log(n) } 
         };
         fetch("/5/wasm") 
            .then(bytes => bytes.arrayBuffer()) 
            .then(module => WebAssembly.instantiate(module, importObj)) 
            .then(finalcode => { 
            console.log(finalcode); 
            console.log(finalcode.instance.exports._Z15fibonacciSeriesi(10)); 
         });
      </script> 
   </body>
</html>)";

static const string file5 = R"(D:\Projects\cxx\WebAssembly\ws4\fib.wasm)";

AddFunction(CFib,5,html5,file5)


static const string html6 = R"(<!DOCTYPE html> 
<html>
   <head> 
      <meta charset="UTF-8">
   </head>
   <body>
      <script> 
        const memory = new WebAssembly.Memory({initial:112});
        fetch("/6/wasm")
            .then(bytes => bytes.arrayBuffer())
            .then(moduel=>WebAssembly.instantiate(moduel,{
                env: {
                  memory: memory,
                  tableBase: 0,
                  __memory_base: 0,
                  __table_base: 0,
                  //mypair: function() {}
                }
            }))
            .then(results=>{
                console.log(results)
                const wasmInstance = results.instance;
                console.log(wasmInstance);
                var buffer = new Int8Array(memory.buffer,0,14);
                
                const code = wasmInstance.exports.mypair(buffer.byteOffset);
                console.log(code);
                console.log(buffer);
                let s = "";
                for (let i = 0; buffer[i] !== 0; ++i) {
                    s += String.fromCharCode(buffer[i]);
                }
                console.log(s);
            })
      </script> 
   </body>
</html>)";

static const string file6 = R"(D:\Projects\cxx\WebAssembly\ws5\pair.wasm)";

AddFunction(CPair,6,html6,file6)