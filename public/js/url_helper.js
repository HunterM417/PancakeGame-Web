/* Based from StackOverflow: https://stackoverflow.com/questions/4656843/jquery-get-querystring-from-url */
function getUrlVars() {
    let vars = {};
    let hashes = decodeURI(window.location.href.slice(window.location.href.indexOf('?') + 1)).split('&');
    for(let i = 0; i < hashes.length; i++) {
        hash = hashes[i].split('=');
        // Check if array of data
        if(hash[0].endsWith('[]')) {
            let key = hash[0].substring(0, hash[0].length-2);
            if(key in vars) {
                vars[key].push(hash[1]);
            } else {
                vars[key] = [ hash[1] ];
            }  
        } else {
            vars[hash[0]] = hash[1];
        }
    }
    return vars;
}