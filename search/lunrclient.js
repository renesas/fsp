"use strict";

var LUNR_CONFIG = {
    "resultsElementId": "searchResults",  // Element to contain results
    "countElementId": "resultCount"  // Element showing number of results
};


// Get URL arguments
function getParameterByName(name, url) {
    if (!url) url = window.location.href;
    name = name.replace(/[\[\]]/g, "\\$&");
    var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
        results = regex.exec(url);
    if (!results) return null;
    if (!results[2]) return "";
    return decodeURIComponent(results[2].replace(/\+/g, " "));
}

function inputClear() {
	document.getElementById("MSearchField").placeholder = "";
}

function inputSet() {
	document.getElementById("MSearchField").placeholder = "Text Search";
}

// Watch input for return - then submit
function inputChange(evt) {
	alert(evt.keyCode);
    var e  = (evt) ? evt : window.event; // for IE
    if (e.keyCode==40 || e.keyCode==13) {
		alert("OK");
		searchLunr("test");
	}
}

//document.getElementById('MSearchField').addEventListener('keyup', function(event) {
//    if (event.code === 'Enter') {
//      event.preventDefault();
//      document.querySelector('form').submit();
//    }
//  });

// Parse search results into HTML
// Results consists of ref number and score for each page (?) the term shows up on
function parseLunrResults(results) {
    var html = [];
    for (var i = 0; i < results.length; i++) {
        console.log("Result = ",results[i])
        var id = results[i]["ref"];
		var term = results[i]["matchData"]["metadata"];
		var pos=[];
		for (var k in term) {
//			console.log("k = ",k);
//			console.log("term[k] - ",term[k]);
//			console.log("term[k]['b']['position'] - ",term[k]["b"]["position"]);
// Get position from "b". "t" = Title, don't need to find pages where only in title
			if ("b" in term[k]) {
				pos = pos.concat(term[k]["b"]["position"]);
			}
//		if ("t" in term[k]) {
//				pos = pos.concat(term[k]["t"]["position"]);
//			}
//			console.log(pos);
		}
//		console.log("pos =",pos);
		var bod = results[i]["matchData"]["metadata"];
        var item = PREVIEW_LOOKUP[id];
        var title = item["t"];
		var preview = "";
        var link = item["l"];
		var numRes = pos.length + " results on page";
		if (pos.length == 1) {
			numRes = pos.length + " result on page";
		}
        var result = ('<p><span class="result-title"><a href="' + link + '?pos=' + pos + '">'
                    + title + '</a></span><br><span class="result-preview">'
                    + preview + '</span>' + '</p>'); // TJ Added "pos"
		if (pos.length != 0) {
			html.push(result);
		}
    }
    if (html.length) {
        return html.join("");
    }
    else {
        return "<p>Your search returned no results.</p>";
    }
}


function escapeHtml(unsafe) {
    return unsafe
         .replace(/&/g, "&amp;")
         .replace(/</g, "&lt;")
         .replace(/>/g, "&gt;")
         .replace(/"/g, "&quot;")
         .replace(/'/g, "&#039;");
}

function countResults(results) {
	var count = 0;
	    for (var i = 0; i < results.length; i++) {
			var term = results[i]["matchData"]["metadata"];
			for (var k in term) {
				if ("b" in term[k]) {
					count = count+1;
				}
			}
		}
	return count;
}

function showResultCount(query, total, domElementId) {
    if (total == 0) {
        return;
    }

    var s = "";
    if (total > 1) {
        s = "s";
    }
    var found = "<p>Found result on " + total + " page" + s;
    if (query != "" && query != null) {
        query = escapeHtml(query);
        var forQuery = ' for <span class="result-query">' + query + '</span>';
    }
    else {
        var forQuery = "";
    }
    var element = document.getElementById(domElementId);
    element.innerHTML = found + forQuery + "</p>";
}


function searchLunr(query) {
    var idx = lunr.Index.load(LUNR_DATA);
    // Write results to page
    var results = idx.search(query);
	// console.log(results);
    var resultHtml = parseLunrResults(results);
    var elementId = LUNR_CONFIG["resultsElementId"];
    document.getElementById(elementId).innerHTML = resultHtml;

//    var count = results.length;
	var count = countResults(results);
    showResultCount(query, count, LUNR_CONFIG["countElementId"]);
	document.getElementById("lunrResultBox").style.display = "block";
}

function closeLunrResults() {
	document.getElementById("lunrResultBox").style.display = "none";
}

// When the window loads, read query parameters and perform search
window.onload = function() {
    var query = getParameterByName("q");
    if (query != "" && query != null) {
        document.forms.lunrSearchForm.q.value = query;
        searchLunr(query);
    }
};