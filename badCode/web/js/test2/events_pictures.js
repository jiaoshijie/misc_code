let img1_li = document.getElementById("img_li1");
let img2_li = document.getElementById("img_li2");
let img3_li = document.getElementById("img_li3");
let img4_li = document.getElementById("img_li4");

/* let img1 = document.getElementById("img1"); */
// let img2 = document.getElementById("img2");
// let img3 = document.getElementById("img3");
/* let img4 = document.getElementById("img4"); */

// img1_li.addEventListener("click", function() {
//   if (img1.className === "hide")
//     img1.className = "";
//   else
//     img1.className = "hide";
// });

img1_li.addEventListener("click", picLink);
img2_li.addEventListener("click", picLink);
img3_li.addEventListener("click", picLink);
img4_li.addEventListener("click", picLink);

function picLink() {
  // console.log(this);

  let picId = this.attributes["data-img"].value;
  let pic = document.getElementById(picId);
  let allImages = document.querySelectorAll("img");

  if(pic.className === "hide") {
    for (let i = 0; i < allImages.length; i++) {
      allImages[i].className = "hide";
    }
    pic.className = "";
  }
  else
    pic.className = "hide";
}
