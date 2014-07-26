<?php
header('Access-Control-Allow-Origin: *'); 
$send = "
<body>
    <style>
        nav {
            background: #00979c;
            color: #fefefe;
            padding: 25px;
        }
        nav ul li{
            list-style: none;
        }
        .console {
            background: #e9e9e9;
            border: solid 1px #999;
            border-radius: 3px;
            min-height: 450px;
        }
    </style>
    <script type='text/javascript'>
        $('document').ready(function () {
            update();
            $('button').each(function () {
                $(this).click(function () {
                    action = $(this).attr('action')
                    b = {
                        url: action,
                        type: 'get',
                        dataType: 'json',
                    };
                    $.ajax(b);
                    update();
                });
            });
            setInterval(update(), 1000);
        });
        function update(){
            $.ajax({
                url: '/?console',
                type: 'get',
                dataType: 'json',
                success: function (data) {
                    if(data.action == '/?ON'){
                        $('#flag').text('The System is down.')
                        $('#power').text('Arm the system.')
                    }else{
                        $('#flag').text('The System is Armed.')
                        $('#power').text('Turn the system off.')
                    }
                    $('#power').attr('action',data.action)   
                    $('#console').html(data.sensorLog)
                    console.log(data)
                }
                ,error: function(xhr, status, error) {
                  console.log(xhr)
                  console.log(status)
                  console.log(error)
                }
            });
        }
    </script>
    <nav class='col-md-12'>
        <ul class='col-md-12'>
            <li class='col-md-1'>
                <img src='http://107.170.57.28/images/logo.png' />
            </li>
            <li class='col-md-3'>
                <h2>Ardu Security</h2>
                <p>Secure, Affordable, and low-energy use.</p>
            </li>
        </ul>
    </nav>
    <section class='col-md-6 text-center'>
        <h1 id='flag'>The system is off.</h1>
        <button action='/?ON' id='power' class='btn btn-primary'>Arm the system</button>
        <button action='/?PLAY' class='btn btn-default'>Play Mario Theme Song</button>
    </section>
    <aside class='col-md-6'>
        <h4>Console</h4>
        <div class='col-md-12 console'><p id='console'></p></div>
    </aside>

</body>";

echo $send;
//echo phpinfo();
?>