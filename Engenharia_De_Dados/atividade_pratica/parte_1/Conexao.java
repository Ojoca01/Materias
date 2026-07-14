import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class Conexao {
// como compilar e executar
// javac -cp ".;postgresql-42.7.2.jar" *.java
// java -cp ".;postgresql-42.7.2.jar" Main
    private static final String URL =
        "jdbc:postgresql://database-aulaengdados-1.c7tpsyn9kbms.us-east-1.rds.amazonaws.com:5432/Universidade";

    private static final String USER =
        "postgresdb1";

    private static final String PASSWORD =
        "g5318246h4l28g4j";

    public static Connection conectar() throws SQLException {
        return DriverManager.getConnection(
            URL,
            USER,
            PASSWORD
        );
    }
}