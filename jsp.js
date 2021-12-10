
window.onload=function () 
{
		clock();
	setInterval(function()
	{
		clock();
	},1000);
 
 
function clock()
{
    //获取显示小时的区域框对象
    var hour = document.getElementById("h");
    //获取显示分钟的区域框对象
    var minute = document.getElementById("m");
    //获取显示秒的区域框对象
    var second = document.getElementById("s");
    
 	    var date = new Date();
        var h = date.getHours();//获取小时
        var m = date.getMinutes();//获取分钟
        var s = date.getSeconds();//获取秒
       
        hour.innerHTML = h;
        minute.innerHTML = m;
        second.innerHTML = s;

    }
}