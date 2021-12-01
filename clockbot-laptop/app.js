var particle = new Particle();
var token;
var deviceId = "NW"; //change this to match your photon name - case sensitive!
//var token = "e1af4f6439213a8610db5df2750c557ac475703c";

particle.login({username: "slbrento@umich.edu", password: "PIxD_SI612"}).then(
    function(data) {
        token = data.body.access_token;
    },
    function(err) {
        console.log('Failed to login to Particle', err);
    }
)

/*****************************************************
 *   Cloud Functions
 * ***************************************************
 *  When you click the happy button, trigger a function
 *  that asks your robot to change its face.
 *  Use name: 'showImage' to load a .bmp file *
 *  Use name: 'face' to draw a pre-defined face or text screen *
 */

 /*  *******************************************************
     EXAMPLE1 of how to draw 2 faces, before and after speaking
     ******************************************************* */
$("#joke").click( function() {
    particle.callFunction({
        deviceId: deviceId,
        name: 'face',  //specify that we want to draw a face
        argument: "misch", //which face we want to draw
        auth: token
    });

    speak("How do you catch a unique rabbit?"); //what should be spoken by app


//below is optional...after timeout of 3000 finish speaking USE THIS
    setTimeout(function(){speak("Unique up on it.");
    	particle.callFunction({
        	deviceId: deviceId,
        	name: 'face',  //specify that we want to draw a face
        	argument: "happy", //which face we want to draw
        	auth: token
    	});
    }, 3000);
});


/*  *******************************************************
    EXAMPLE2 of how to write text to the screen while speaking
    ******************************************************* */

$("#Help").click( function() {
    particle.callFunction({
        deviceId: deviceId,
        name: 'writeMessage', //specify we want to write text to TFT
        argument: "How can I help you?", //text to write to the TFT
        auth: token
    });
    speak("How can I help you?"); //what the app should speak
});


/*  *******************************************************************
    EXAMPLE3 of how to display an image from the micro sd card
    To get custom images you can convert them to BMP format - True Color 24
    at this website https://online-converting.com/image/convert2bmp/
    File names must be 8 characters or fewer and end in .bmp USE THIS
    ********************************************************************  */
$("#Darth").click( function() {
    particle.callFunction({
        deviceId: deviceId,
        name: 'showImage', //specify we want to draw a BMP imgae
        argument: "/popcorn.bmp", //the specific BMP image to show...saved on micro SD card
        auth: token
    });
    speak("Luke, I am your father.");
});






/*************************************************************
   LEAVE THIS CODE AS IS - Advanced Speech Synthesis
 ************************************************************* */

//speak button
$("#speak").click(function() {
    var text = $("#speech").val();
    speak(text);
});

//speak and write to screen button
$("#speakAndWrite").click(function() {
    var text = $("#speech").val();
    speak(text);
    particle.callFunction({
        deviceId: deviceId,
        name: 'writeMessage', //specify we want to write text to TFT
        argument: text, //text to write to the TFT
        auth: token
    });
});

function speak(text) {
    // Create an utterance to be spoken by the Web Speech API
    var msgConfig = new SpeechSynthesisUtterance();

    // Get all the possible voices
    var voices = window.speechSynthesis.getVoices();

    // Set the voice to be Victoria
    msgConfig.voice = voices.filter(function(voice) {return voice.name === "Victoria"})[0]; //Kyoko or Victoria

    // Reduce the pitch so the voice sounds more robotic. Values are between 0 and 2
    msgConfig.pitch = "1.0";

    // Speed up the voice so it sounds more robotic. Values can be between 0.1 and 10
    msgConfig.rate = "1.0";

    // Set the text we are going to say.
    msgConfig.text = text;

    // Ask Web Speech API to say our utterance, in the voice we configured.
    window.speechSynthesis.speak(msgConfig);
}
