const express = require("express");
const app = express();

app.get("/menu", function (req, res) {
    res.sendFile(__dirname + "/indexMenu.html");
});

app.get("/login", function (req, res) {
    res.sendFile(__dirname + "/indexLogin.html");
});

app.get("/adm", function (req, res) {
    res.sendFile(__dirname + "/indexAdm.html");
});

app.get("/produtos", function (req, res) {
    res.sendFile(__dirname + "/indexProdutos.html");
});

app.get("/carrinho", function (req, res) {
    res.sendFile(__dirname + "/indexCarrinho.html");
})
app.listen(8000, function () {
    console.log(`Server is running on http://localhost:8000/menu`);
});