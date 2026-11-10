#include "ServerProject/pages.hpp"

namespace Pages {

const char index_html[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Web Server</title>
    <style>
        .container {
            width: 100%;
            display: flex;
            flex-direction: column;
        }
        .header {
            width: 100%;
            display: flex;
            justify-content: center;
            flex-grow: 0;
        }
        .body {
            display: flex;
            flex-grow: 1;
            display: flex;
        }
        table {
            border: 4px solid darkgrey;
        }
        td {
            border: 1px solid grey;
            padding: 4px;
            margin-right: 0px;
            font-size: x-large;
            min-height: 160px;
            min-width: 160px;
            margin: 10px;
        }
        button {
            min-height: 160px;
            min-width: 160px;
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>HVRC Control system</h1>
        </div>
        <div class="body">
            <table>
                <tbody>
                    <tr>
                        <td>Current Time Remaining</td>
                        <td id="current-time"></td>
                        <td><button id="refresh">Refresh</button></td>
                        <td><button id="clear-time">Clear</button></td>
                    </tr>
                    <tr>
                        <td><button id="add-five">+5 min</button></td>
                        <td><button id="add-ten">+10 min</button></td>
                        <td><button id="add-twenty">+20 min</button></td>
                        <td><button id="add-thirty">+30 min</button></td>
                    </tr>
                </tbody>
            </table>
        </div>
    </div>
    <script>
        var currentTimeField = document.getElementById("current-time");
        var currentTime = 0;
        var addFiveButton = document.getElementById("add-five");
        var addTenButton = document.getElementById("add-ten");
        var addTwentyButton = document.getElementById("add-twenty");
        var addThirtyButton = document.getElementById("add-thirty");
        var clearTimeButton = document.getElementById("clear-time");
        var refreshButton = document.getElementById("refresh");
        currentTimeField.innerText = "0 minutes";

        function addTime(minutes) {
            return function() {
                fetch('/addTime?value=' + minutes)
                    .then(function(response) {
                        return response.json();
                    })
                    .then(function(jsonResponse) {
                        currentTime = jsonResponse['minutes'];
                        currentTimeField.innerText = currentTime + ' minutes'
                    })
                console.log(minutes)
            }
        }

        addFiveButton.onclick = addTime(5);
        addTenButton.onclick = addTime(10);
        addTwentyButton.onclick = addTime(20);
        addThirtyButton.onclick = addTime(30);
        refreshButton.onclick = addTime(0);
        addTime(0)();

        function clearTime() {
            fetch('/clearTime')
                .then(function(response) {
                    return response.json();
                })
                .then(function(jsonResponse) {
                    currentTime = jsonResponse['minutes'];
                    currentTimeField.innerText = currentTime + ' minutes'
                })
        }
        clearTimeButton.onclick = clearTime

        function decrementCurrentTime() {
            currentTime -= 1;
            if (currentTime < 0) {
                currentTime = 0;
            }
            currentTimeField.innerText = currentTime + ' minutes';
        }
        setInterval(decrementCurrentTime, 1000*60)
    </script>
</body>
</html>
)rawliteral";
}
