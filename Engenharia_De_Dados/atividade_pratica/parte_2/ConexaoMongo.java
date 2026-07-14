import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoDatabase;
public class ConexaoMongo {
    /*
     * Altere somente o IP caso sua EC2 mude.
     * Exemplo:
     * mongodb://IP_DA_EC2:27017/
     */
    // como compilar e executar
    // javac -cp ".;bson-5.1.0.jar;mongodb-driver-core-5.1.0.jar;mongodb-driver-sync-5.1.0.jar" *.java
    // java -cp ".;bson-5.1.0.jar;mongodb-driver-core-5.1.0.jar;mongodb-driver-sync-5.1.0.jar" Main
    
    private static final String URI =  "mongodb://52.90.160.240:27017/";
    private static final String BANCO =  "Universidade";
    private static MongoClient cliente;
    public static MongoDatabase conectar() {
        if (cliente == null) {
            try {
                cliente = MongoClients.create(URI);
                System.out.println(
                        "Conectado ao MongoDB."
                );
            } catch (Exception e) {
                System.out.println(
                        "Erro ao conectar MongoDB: "
                        + e.getMessage()
                );
                throw e;
            }
        }
        return cliente.getDatabase(BANCO);
    }
    public static void fechar() {
        if (cliente != null) {
            cliente.close();
            cliente = null;
            System.out.println(
                    "Conexão MongoDB encerrada."
            );
        }
    }
}