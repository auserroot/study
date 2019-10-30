function checkbox()
{		var k=0;
		var checkbox4 = document.getElementsByName("q4");
	//遍历选项组中的所有选项
	for(var i = 0; i < checkbox4.length; i++) 
	{
	     if(checkbox4[i].checked) 
	        {
	           k++;
	        }
    }
		if(k == 0) 
		{
		   alert("第4题起码要选择一个选项。");
		   return false;
		}	
			var j=0;
		var checkbox5 = document.getElementsByName("q5");
	//遍历选项组中的所有选项
	for(var i = 0; i < checkbox5.length; i++) 
	{
	     if(checkbox5[i].checked) 
	        {
	           j++;
	        }
    }
		if(j == 0) 
		{
		   alert("第5题起码要选择一个选项。");
		   return false;
		}	
}

function check ()
{
	checkbox();
	
}
	
