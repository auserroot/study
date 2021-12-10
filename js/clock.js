function drawClock()
{
	
	var c=document.getElementById("clock");
	var sz=c.getContext("2d");
	
	/*清空画布*/
    sz.clearRect(0, 0,300,300);
	/*获取时间*/
    var now =new Date();
    var second =now.getSeconds();
    var minute =now.getMinutes();
    var hour1 =now.getHours();
    /*将24小时进制转为12小时，且为浮点型*/
    var hour=hour1+minute/60;
    //hour=hour>12 ?hour-12:hour;
    if(hour>12)
    {
    	hour=hour-12;
    }
    /*获取全部时间*/
    var time=now.toLocaleString( );
    
	/*绘制时钟刻度*/
	for(var i=0;i<12;i++)
	{
       sz.save();
       sz.lineWidth=3;
       sz.strokeStyle="black"
       sz.translate(150,150);/*圆心*/
       sz.rotate(i*30*Math.PI/180);
       sz.beginPath();
       sz.moveTo(0,120);
       sz.lineTo(0,90);
       sz.closePath();
       sz.stroke();
       sz.restore();
    }
 
     
    for(var i=0;i<60;i++)
    {
        sz.save();
        sz.lineWidth=1.5;
        sz.strokeStyle="black"
        sz.translate(150,150);
        sz.rotate(i*6*Math.PI/180);
        sz.beginPath();
        sz.moveTo(0,126);
        sz.lineTo(0,120);
        sz.closePath();
        sz.stroke();
        sz.restore();
    }
        	
        sz.beginPath();
        sz.lineWidth=1;
        sz.fillStyle="black";
        sz.arc(150,150,5,0,360,false);
        sz.fill();
        sz.stroke(); 
        sz.closePath();
        
        //外边框
        sz.beginPath();
        sz.lineWidth=10;
        sz.strokeStyle="darkgray";
        sz.arc(150,150,135,0,360,false);
        sz.stroke(); 
        sz.closePath();
        
        //时针
        sz.save();
        sz.lineWidth=5;
        sz.strokeStyle="black";
        sz.translate(150,150);
        sz.rotate(hour*30*Math.PI/180);
        sz.beginPath();     
        sz.moveTo(0,-80);
        sz.lineTo(0,20);
        sz.closePath();
        sz.stroke();
        sz.restore();
        
        //分针
        sz.save();
        sz.lineWidth="3";
        sz.strokeStyle="black";
        sz.translate(150,150);
        sz.rotate(minute*6*Math.PI/180);
        sz.beginPath();     
        sz.moveTo(0,-110);
        sz.lineTo(0,20);
        sz.closePath();
        sz.stroke();
        sz.restore();
        
        //秒针
        sz.save();
        sz.lineWidth="2";
        sz.strokeStyle="red";
        sz.translate(150,150);
        sz.rotate(second*6*Math.PI/180);
        sz.beginPath();     
        sz.moveTo(0,-130);
        sz.lineTo(0,20);
        sz.closePath();
        sz.stroke();
        sz.beginPath();
        sz.strokeStyle="red";
        sz.closePath();
        sz.stroke();
        sz.restore();
        
         
        
}
    setInterval("drawClock()", 1000);
