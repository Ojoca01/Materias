// Importa o módulo principal do Three.js diretamente da CDN
import * as THREE from 'https://cdn.jsdelivr.net/npm/three@0.160.0/build/three.module.js';

// === CENA, CÂMERA E RENDERIZADOR ===
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer({ canvas: document.querySelector('.webgl'), antialias: true });
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));

// === GERAR AS ESTRELAS ===
const starGeometry = new THREE.BufferGeometry();
const starCount = 5000;
const positions = new Float32Array(starCount * 3);

for (let i = 0; i < starCount * 3; i++) {
    positions[i] = (Math.random() - 0.5) * 2000; // distribui as estrelas
}
starGeometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));

const starMaterial = new THREE.PointsMaterial({ color: 0xffffff, size: 0.8 });
const stars = new THREE.Points(starGeometry, starMaterial);
scene.add(stars);

// === LUZ E CÂMERA ===
camera.position.z = 500;

// === ANIMAÇÃO ===
function animate() {
    requestAnimationFrame(animate);

    // Efeito de rotação da galáxia
    stars.rotation.y += 0.0008;
    stars.rotation.x += 0.0004;

    renderer.render(scene, camera);
}
animate();

// === REDIMENSIONAMENTO ===
window.addEventListener('resize', () => {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
});
