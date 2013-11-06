window.addEventListener("load",function() {
	document.getElementById("signUpForm").addEventListener("submit",function(eve) {
		if(document.getElementById("psw").value != 
			document.getElementById("verifyPsw").value) {
				eve.preventDefault();
		}
	});
});
