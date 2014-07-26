if (!Date.prototype.toISOString) {
    (function () {

        function pad(number) {
            var r = String(number);
            if (r.length === 1) {
                r = '0' + r;
            }
            return r;
        }

        Date.prototype.toISOString = function () {
            return this.getUTCFullYear() + '-' + pad(this.getUTCMonth() + 1) + '-' + pad(this.getUTCDate()) + 'T' + pad(this.getUTCHours()) + ':' + pad(this.getUTCMinutes()) + ':' + pad(this.getUTCSeconds()) + '.' + String((this.getUTCMilliseconds() / 1000).toFixed(3)).slice(2, 5) + 'Z';
        };

    }());
}
$('document').ready(function () {
    var date = new Date(),
        now = date.toISOString();

//    var past = new Date(date - 10800000),
//    var past = new Date(date - 21600000),
    var past = new Date(date - 86400000),
        pastStr = past.toISOString()
    console.log("start: "+pastStr)
    console.log("end: "+now)

    $.ajax({
        url: 'http://api.xively.com/v2/feeds/1553462817?start=' + pastStr + '&end=' + now + '&interval=60',
        type: 'get',
        dataType: 'json',
        beforeSend: function (xhr) {
            xhr.setRequestHeader('X-ApiKey', 'djBr2cpg1hnc5N5h3qoFXP4pDlKsed2aYO0Exm14zVtGbyCx ');
        },
        success: function (response) {
            canvi(response);
        }
    }) //.ajax
})

function canvi(response) {
    var canvi = {}
    for (var i = 0; i <= response.datastreams.length - 1; i++) {
        var dataVals = [],
            times = []
        for (var point = 0; point <= response.datastreams[i].datapoints.length - 1; point++) {

            if (response.datastreams[i].datapoints[point] != undefined) {
                dataVals.push(response.datastreams[i].datapoints[point].value);

                var timestamp = new Date(response.datastreams[i].datapoints[point].at);
                console.log(timestamp.getTimezoneOffset() * 60000)
                timestamp = new Date(timestamp.getTime() + (timestamp.getTimezoneOffset() * 60000));
                timestamp = timestamp.getHours() + ":" + timestamp.getMinutes();
                times.push(timestamp);
            }
        }

        $('#graphs').append('<li><h3 class="col-md-8">' + response.datastreams[i].id + '</h3><h4 class="col-md-4">Current Value: '+ response.datastreams[i].current_value +'</h4><canvas id="graph' + i + '" height="400" width="996" /><li>')

        canvi[i] = {}
        canvi[i].canvas = document.getElementById('graph' + i)
        canvi[i].ctx = canvi[i].canvas.getContext("2d")
        canvi[i].data = {
            labels: times,
            datasets: [
                {
                    fillColor: "rgba(49,95,147,0.5)",
                    strokeColor: "#315F93",
                    data: dataVals
                    }
                ]
        };
    }
    chartIt(canvi)
}

function chartIt(canvi) {
    for (var i in canvi) {
        console.log(canvi[i].data.labels)
        new Chart(canvi[i].ctx).Line(canvi[i].data, {pointDot: false});
    }
    //        new Chart(canvi[0].ctx).Line(canvi[0].data);
}

function workingChart() {
    var ctx = $("#myChart").get(0).getContext("2d");
    //This will get the first returned node in the jQuery collection.
    var myNewChart = new Chart(ctx);

    data = {
        "labels": ["2:58", "2:59", "3:0", "3:1", "3:2", "3:3", "3:4", "3:5", "3:6", "3:7", "3:8", "3:9", "3:10", "3:11", "3:12", "3:13", "3:14", "3:15", "3:16", "3:28", "4:4", "4:5", "4:6", "4:7", "4:8", "4:9", "4:10", "4:12", "4:13", "4:14", "4:15", "4:16", "4:17", "4:18", "4:19", "4:20", "4:21", "4:22", "4:23", "4:24", "4:25", "4:26", "4:27", "4:28", "4:29", "4:30", "4:31", "4:32", "4:33", "4:34", "4:35", "4:36", "4:37", "4:38", "4:39", "4:40", "4:41", "4:42", "4:43"],
        "datasets": [{
            "fillColor": "#315F93",
            "strokeColor": "#315F93",
            "pointColor": "#315F93",
            "pointStrokeColor": "#fff",
            "data": ["67.00", "67.00", "67.00", "68.00", "68.00", "68.00", "70.00", "68.00", "70.00", "70.00", "71.00", "71.00", "71.00", "71.00", "71.00", "71.00", "73.00", "73.00", "73.00", "68.00", "68.00", "67.00", "68.00", "69.00", "69.00", "69.00", "67.00", "67.00", "69.00", "69.00", "70.00", "70.00", "70.00", "72.00", "72.00", "72.00", "72.00", "72.00", "72.00", "70.00", "70.00", "69.00", "69.00", "69.00", "67.00", "67.00", "67.00", "69.00", "69.00", "69.00", "70.00", "70.00", "70.00", "70.00", "72.00", "72.00", "72.00", "72.00", "72.00"]
        }]
    }
    options = {
        pointDot: false
    }

    new Chart(ctx).Line(data, options);
}