window.addEventListener("load",function() {
	document.getElementById("signUpForm").addEventListener("submit",function(eve) {
		var errmsg = document.getElementById("errmsg");
		errmsg.style.display = "none";
		if(document.getElementById("psw").value != 
			document.getElementById("verifyPsw").value) {
				eve.preventDefault();
				errmsg.style.display = "inline";
		}
	});
});
