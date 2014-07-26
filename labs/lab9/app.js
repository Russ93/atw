var express = require('express');
var http = require('http');
var app = express();

var app = express();
var httpServer = http.createServer(app);

var twitterAPI = require('node-twitter-api');

var twitter = new twitterAPI({
	consumerKey: '6cavnitPm5K3ZPb3D3ZcQYzvN',
	consumerSecret: 'VqywcK689CGsQlMrqi5Es0YNBzqiEFhS1kO7NYI2Dhw2Lf0BmP'
});

var credentials = {}

app.get('/', function(req, res){

	twitter.getRequestToken(function(error, requestToken, requestTokenSecret, results){

		if (error) {

			res.send("Error getting OAuth request token : " + error);

		} else {

			credentials.requestToken = requestToken;
			credentials.requestTokenSecret = requestTokenSecret;

			twitter.getTimeline(
				"home", 
				{
					screen_name: "cuppajoe2"
				},
				"2527454822-hCvSHgXLFUP3lCU0GF8HQ99h8fchA8mZ3opTfV4",
				"xoaCdfX5kxB4bE1iqeHEER6b0frwCie0HtLSvleOqaqSO",
				function(error, data, response) {
					if (error) {
						res.send("Error getting timeline : " + error);
					} else {
						var words, light;

						light = 0;

						words = data[0].text.split(' ');

						for(i in words){
							if (words[i] == "#cuppajoe" || words[i] == "#cuppajoe2"){
								light = 1;
							}else if(words[i] == "#cuppajoestop" || words[i] == "#cuppajoe2stop"){
								light = 0;
							}
						}

						res.send("#"+light);
					}
			});

		}

	});

});

app.get('/what', function(req, res){

	twitter.getRequestToken(function(error, requestToken, requestTokenSecret, results){

		if (error) {

			res.send("Error getting OAuth request token : " + error);

		} else {

			credentials.requestToken = requestToken;
			credentials.requestTokenSecret = requestTokenSecret;

			twitter.getTimeline(
				"home", 
				{
					screen_name: "cuppajoe2"
				},
				"2527454822-hCvSHgXLFUP3lCU0GF8HQ99h8fchA8mZ3opTfV4",
				"xoaCdfX5kxB4bE1iqeHEER6b0frwCie0HtLSvleOqaqSO",
				function(error, data, response) {
					if (error) {
						res.send("Error getting timeline : " + JSON.stringify(error));
					} else {

						res.send("data: "+JSON.stringify(data));
					}
			});

		}

	});

});

httpServer.listen(5000, function() {
	console.log('Express server listening on port 3000');
});