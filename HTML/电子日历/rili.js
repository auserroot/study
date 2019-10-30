    var date=new Date();
    var year=date.getFullYear();
    var month=date.getMonth()+1;
    var day=date.getDate();
    var allday=0;
 
    function count() {
        if (month != 2) {
            if ((month == 4) || (month == 6) || (month == 9) || (month == 11)) {
                allday = 30;
            }
            else {
                allday = 31;
            }
        }
        else {
            if (((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0) {
                allday = 29;
            }
            else {
                allday = 28;
            }
        }
    }
 
    function showDate(){
        showMonth();
        count();
        var firstdate=new Date(year,month-1,1);
        var xiqi=firstdate.getDay();
        var daterow=document.getElementById("day");
        daterow.innerHTML=" ";
        if(xiqi!=0){
            for(var i=0;i<xiqi;i++){
                var dayElement=document.createElement("div");
                dayElement.className="day";
                daterow.appendChild(dayElement);
            }
        }
        for(var j=1;j<=allday;j++){
            var dayElement =document.createElement("div");
            dayElement.className="day";
            dayElement.innerHTML=j+"";
            if(j==day){
                dayElement.style.color="red";
            }
            daterow.appendChild(dayElement)
        }
    }
    
    function lastMonth(){
        if(month>1){
            month-=1;
        }
        else{
            month=12;
            year-=1;
        }
        showDate();
    }
    
     function showMonth(){
        var year_month=year+"年"+month+"月";
        document.getElementById("month").innerHTML=year_month;
    }
 
    function nextMonth(){
        if(month<12){
            month+=1;
        }else{
            month=1;
            year+=1;
        }
        showDate();
    }