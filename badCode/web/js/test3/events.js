let checkList = document.getElementById("checklist");

let items = checkList.querySelectorAll("li");
let inputs = checkList.querySelectorAll("input");

// items[0].className = "edit"

for (let i = 0; i < items.length; i++)
{
  items[i].addEventListener("click", editItem);
  inputs[i].addEventListener("blur", updateItems);
  inputs[i].addEventListener("keypress", keyPress);
}

function editItem() {
  this.className = "edit";
  let input = this.querySelector("input");
  input.focus();
  input.setSelectionRange(0, input.value.length);
}

function updateItems() {
  this.previousElementSibling.innerHTML = this.value;
  this.parentNode.className = "";
}

function keyPress() {
  if(event.which === 13)
    updateItems.call(this);
}
