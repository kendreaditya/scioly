const PATH = "https://maps.googleapis.com/maps/api/place/nearbysearch/json?";
const key = "AIzaSyApZIzfuIWCGDUfiMsHPbAuhl2InxKfwP8"; // API key
const location = "40.2400,-77.0620";  // lat & long of location
const radius = "2000"; // radius around location in meters (max: 50 000)

var URL = PATH+"location="+location+"&radius="+radius+"&key="+key;

const fetch = require('node-fetch');
let settings = {method: "Get"};

var obj = new Array();
fetch(URL, settings).then(res => res.json()).then((json) => {
    for(let i=0; i<json.results.length; i++)
    {
        obj.push(json.results[i].name)
    }
    console.log(obj);
});