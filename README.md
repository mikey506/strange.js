# weird.js
weird.js is a JavaScript obfuscation compiler written in C. It is designed to generate obfuscated JavaScript code using a limited set of characters: [()]!+-/*=>.

## Building

    make

## Usage

To obfuscate a JavaScript file using weird.js, use the following command:

    ./weird [OPTIONS] in.js out.js
    
The [OPTIONS] parameter is optional. One available option is -m, which disables wrapping the final code in an eval statement.

## How does this work?
weird.js utilizes type coercion to produce obfuscated yet functional JavaScript code. By leveraging implicit conversions and JavaScript's flexible type system, weird.js transforms the code into an unreadable form while preserving its functionality.

If you're interested in learning more about the underlying obfuscation techniques employed by weird.js, I recommend watching this video by Low Level Javascript.

I recommed checking out [this video by Low Level Javascript](https://www.youtube.com/watch?v=sRWE5tnaxlI) if you're interested in learning more.

## Runtimes
### Node.js
When using weird.js with Node.js and the require function, you need to define require explicitly. Here's an example of how to define require: 

    const require = new Function("var require = global.require || global.process.mainModule.constructor._load; return require")();

## Support
Support for weird.js is available on [IRC](https://webchat.ephasic.org/?join=ephasic)
