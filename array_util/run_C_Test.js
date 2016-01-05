var fs = require('fs');
var child_process = require('child_process');

var text =  fs.readFileSync('./'+process.argv[2],'utf-8');

var tests = text.match(/test\w+/g);

tests = tests.map(function(test){
	return test+"\(\);";
})

var sample = [
	"#include <stdio.h>",
	"#include \"arrayUtil_test.C\"",
	"int main(void) {"
]


var main = sample.join('\n')+'\n'+tests.join('\n')+'\n}';

fs.writeFileSync('test_main.c',main)

child_process.execSync('gcc test_main.c array_util.c -o arrayUtilTest')
child_process.execSync('./arrayUtilTest')


