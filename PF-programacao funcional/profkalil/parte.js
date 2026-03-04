const startGameBtn = document.getElementById("startGame");
const playerNameInput = document.getElementById("playerName");
const playerNameDisplay = document.getElementById("playerNameDisplay");
const loginScreen = document.getElementById("login-screen");
const gameInterface = document.getElementById("game-interface");
const faseSelect = document.getElementById("faseSelect");
const fase1Container = document.getElementById("fase1-container");
const fase2Container = document.getElementById("fase2-container");
const grid1 = document.querySelector(".grid1");
const grid2 = document.querySelector(".grid2");

startGameBtn.addEventListener("click", () => {
  const playerName = playerNameInput.value.trim();
  if (playerName === "") {
    alert("Por favor, insira seu nome.");
    return;
  }

  const selectedPhase = faseSelect.value;

  playerNameDisplay.textContent = playerName;
  loginScreen.style.display = "none";
  gameInterface.style.display = "flex";

  if (selectedPhase === "fase1") {
    fase1(); // Chamada para montar as cartas
    fase1Container.style.display = "block";
    fase2Container.style.display = "none";
  } else if (selectedPhase === "fase2") {
    fase2(); // Chamada para montar as cartas
    fase2Container.style.display = "block";
    fase1Container.style.display = "none";
  }
});

function fase1() {
  console.log("Fase 1 carregando...");
  const comidas = ["pizza", "batata", "arroz", "bife", "doce", "sorvete"];
  const cartas = [...comidas, ...comidas];
  const embaralhado = cartas.sort(() => 0.5 - Math.random());

  grid1.innerHTML = ""; // Limpa a grade

  embaralhado.forEach((comida) => {
    const card = document.createElement("img");
    card.src = `imagens/${comida}.png`;
    card.classList.add("card-img");
    grid1.appendChild(card);
  });
}

function fase2() {
  console.log("Fase 2 carregando...");
  const natureza = ["arvore", "flor", "fogo", "folha", "lua", "sol"];
  const cartas = [...natureza, ...natureza];
  const embaralhado = cartas.sort(() => 0.5 - Math.random());

  grid2.innerHTML = ""; // Limpa a grade

  embaralhado.forEach((item) => {
    const card = document.createElement("img");
    card.src = `imagens/${item}.jpg`;
    card.classList.add("card-img");
    grid2.appendChild(card);
  });
}
