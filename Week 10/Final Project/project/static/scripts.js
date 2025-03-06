// Search script in the header
let input = document.querySelector('input');
input.addEventListener('input', async function() {
    let response = await fetch('/search?q=' + input.value);
    let shows = await response.text();
    document.querySelector('ul').innerHTML = shows;
});

// Increase and decrease the instructions and ingredients quantity
function ajouterEtape_modify(classe) {
    var container = document.getElementById(classe + "s");
    var textareas = container.getElementsByClassName(classe);
    var nombreEtapes = textareas.length;
    var textarea = document.createElement("textarea");
    textarea.className = classe;
    textarea.name = classe + (nombreEtapes + 1);
    textarea.placeholder = classe.charAt(0).toUpperCase() + classe.slice(1) + " " + (nombreEtapes + 1);
    container.appendChild(textarea);
}

function supprimerEtape_modify(classe) {
    var container = document.getElementById(classe + "s");
    var textareas = container.getElementsByClassName(classe);
    if (textareas.length > 1) {
        container.removeChild(textareas[textareas.length - 1]);
    }
}

var nombreEtapes = 1;

function ajouterEtape_add() {
    nombreEtapes++;
    var container = document.getElementById("instructions");
    var textarea = document.createElement("textarea");
    textarea.name = "instruction" + nombreEtapes;
    textarea.placeholder = "Instruction " + nombreEtapes;
    container.appendChild(textarea);
}

function supprimerEtape_add() {
    if (nombreEtapes > 1) {
        var container = document.getElementById("instructions");
        container.removeChild(container.lastChild);
        nombreEtapes--;
    }
}

var nombreingredients = 1;

function ajouterEtape2_add() {
    nombreingredients++;
    var container2 = document.getElementById("ingredients");
    var textarea2 = document.createElement("textarea");
    textarea2.name = "ingredient" + nombreingredients;
    textarea2.placeholder = "Ingredient " + nombreingredients;
    container2.appendChild(textarea2);
}

function supprimerIngredient_add() {
    if (nombreingredients > 1) {
        var container = document.getElementById("ingredients");
        container.removeChild(container.lastChild);
        nombreingredients--;
    }
}

// It shows the results of search button header, its for fixing a bug about click-links
document.addEventListener('DOMContentLoaded', function() {
    var searchInput = document.querySelector('.search-button2');
    var searchList = document.querySelector('.search-list');
    searchInput.addEventListener('focus', function() {
        searchList.style.display = 'block';
    });
    document.addEventListener('click', function(event) {
        var targetElement = event.target;

        do {
            if (targetElement == searchList || targetElement == searchInput) {
                return;
            }
            targetElement = targetElement.parentNode;
        } while (targetElement);
        searchList.style.display = 'none';
    });
});

// It takes the name = 'q' value from search rectangle from the header, and redirect to /search2
function submitToSearch2() {
    var searchForm = document.getElementById('searchForm');
    var searchQuery = searchForm.q.value;
    var searchAction = '/search2';
    window.location.href = searchAction + '?q=' + encodeURIComponent(searchQuery);
}
