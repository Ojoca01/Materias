import java.sql.*;
import java.util.Arrays;

public class UsuarioDAO {

    public void listarUsuarios() {

        String sql =
                "SELECT * FROM universidade.usuario";

        try (
                Connection conn = Conexao.conectar();
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery(sql)
        ) {

            while (rs.next()) {

                Array emailArray = rs.getArray("email");

                String[] emails =
                        emailArray == null
                                ? null
                                : (String[]) emailArray.getArray();

                System.out.println(
                        rs.getString("cpf")
                                + " | "
                                + rs.getString("nome")
                                + " | "
                                + Arrays.toString(emails)
                );
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void inserirUsuario(
            String cpf,
            String nome,
            Date nascimento,
            String email,
            String telefone,
            String login,
            String senha
    ) {

        String sql =
                "INSERT INTO universidade.usuario " +
                "(cpf,nome,data_nascimento,email,telefone,login,senha) " +
                "VALUES (?,?,?,?,?,?,?)";

        try (
                Connection conn = Conexao.conectar();
                PreparedStatement ps =
                        conn.prepareStatement(sql)
        ) {

            ps.setLong(1, Long.parseLong(cpf));
            ps.setString(2, nome);
            ps.setDate(3, nascimento);

            Array emailArray =
                    conn.createArrayOf(
                            "varchar",
                            new String[]{email}
                    );

            Array telefoneArray =
                    conn.createArrayOf(
                            "varchar",
                            new String[]{telefone}
                    );

            ps.setArray(4, emailArray);
            ps.setArray(5, telefoneArray);

            ps.setString(6, login);
            ps.setString(7, senha);

            ps.executeUpdate();

            System.out.println("Usuário inserido!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void atualizarEmail(
            String cpf,
            String novoEmail
    ) {

        String sql =
                "UPDATE universidade.usuario " +
                "SET email = ? " +
                "WHERE cpf = ?";

        try (
                Connection conn = Conexao.conectar();
                PreparedStatement ps =
                        conn.prepareStatement(sql)
        ) {

            Array emailArray =
                    conn.createArrayOf(
                            "varchar",
                            new String[]{novoEmail}
                    );

            ps.setArray(1, emailArray);
            ps.setLong(2, Long.parseLong(cpf));

            ps.executeUpdate();

            System.out.println("Usuário atualizado!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void removerUsuario(
            String cpf
    ) {

        String sql =
                "DELETE FROM universidade.usuario " +
                "WHERE cpf = ?";

        try (
                Connection conn = Conexao.conectar();
                PreparedStatement ps =
                        conn.prepareStatement(sql)
        ) {

            ps.setLong(1, Long.parseLong(cpf));

            ps.executeUpdate();

            System.out.println("Usuário removido!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}