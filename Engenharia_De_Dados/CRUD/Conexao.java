import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class Conexao {

    private static final String URL =
        "jdbc:postgresql://database-aulaengdados-1.c7tpsyn9kbms.us-east-1.rds.amazonaws.com:5432/postgres";

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