var Sensor =
{
	value: 0,
	endPoint:"http://130.206.82.44:1026/NGSI10/contextEntities/",
	get: function(idSensor,Callback,Error)
	{
		Callback = Callback || "";
		Error = Error || "";
		var uri = Sensor.endPoint+idSensor;
		Xhr.get(uri,"Sensor.get("+idSensor+")",200);
	}
}



//==========================================
var Xhr=
{
	createCORS:function(method, url)
	{
    	var xhr = new XMLHttpRequest();
    	if ("withCredentials" in xhr)
    	{
			// Check if the XMLHttpRequest object has a "withCredentials" property.
			// "withCredentials" only exists on XMLHTTPRequest2 objects.
			xhr.open(method, url, true);
    	}else if (typeof XDomainRequest != "undefined") 
    	{
	    	// Otherwise, check if XDomainRequest.
	    	// XDomainRequest only exists in IE, and is IE's way of making CORS requests.
	    	xhr = new XDomainRequest();
	    	xhr.open(method, url);
    	}else 
    	{
			// Otherwise, CORS is not supported by the browser.
			xhr = null;
    	}
    	return xhr;
    },
	get: function(endPoint,nameFuntion,statusOk,Callback,Error)
	{
		Callback = Callback || "";
		var xhr = Xhr.createCORS("GET", endPoint);
		if (!xhr)
		{
			throw new Error('CORS not supported');
			return;
		} 	
		xhr.onreadystatechange = function(Callback)
		{
			return function()
			{
				if (xhr.readyState==4 && xhr.status == statusOk)
				{
					if(typeof(Callback) == typeof(Function))
					{
						if(Settings)
				   			Callback(xhr.response);							
						else
				   			Callback(xhr.responseText);
				   	}
				}
				else if (xhr.readyState==4)
				{
					if(Error)
						Error();
					console.log("Error: "+nameFuntion+" "+ xhr.status);
					return false;
				}
			}
		}(Callback);

		xhr.onerror = function () 
		{
			console.log("Error: "+nameFuntion);
			if(Error)
				Error();
			return false;		
		};
		if (xhr.overrideMimeType) 
		{
			xhr.overrideMimeType('text/plain; charset=x-user-defined');
		}

	  	//xhr.setRequestHeader("Content-type", "application/json; charset=UTF-8");
	  	//xhr.setRequestHeader("Accept", "application/json; charset=UTF-8");
		xhr.send(); 	
	}
}
