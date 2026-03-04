class Animal {
    void fazerSom() {
        System.out.println("O Dinossauro faz um som");
    }
}

class Cachorro extends Animal {
    Cachorro cachorro;
    @Override
    void fazerSom() {
        super.fazerSom(); // Chama o método da classe Pai
        System.out.println("O cachorro late");
    }
}
