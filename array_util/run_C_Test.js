var fs = require('fs');
var child_process = require('child_process');
var testfile = process.argv[2];

var text =  fs.readFileSync('./'+testfile,'utf-8');

var tests = text.match(/test\w+\(\)/g);

tests = tests.map(function(test){
	return test+";";
})

var sample = [
	"#include <stdio.h>",
	"#include \""+testfile+"\"",
	"int main(void) {"
]

var count = tests.length;
var runTest = function(){
	child_process.execSync('./arrayUtilTest');
	return 1;
}
tests.forEach(function(test){
	var main = sample.join('\n')+'\n'+test+'\n\n}';
	fs.writeFileSync('test_main.c',main)
	child_process.execSync('gcc test_main.c array_util.c -o arrayUtilTest')
	if(runTest()==1) console.log(test.substr(0,test.length-3));
	console.log("--------------------------------------------")
	
})


