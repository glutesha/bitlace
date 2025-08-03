fetch("/api/settings").then(r => r.json()).then(r => {
    for (let s in r) {
        if(s != "hidden"){
            document.getElementById(s).value = r[s];
        }
    }
    document.getElementById("hidden").checked = r["hidden"];
    document.getElementById("flip").checked = r["flip"];
})