import java.sql.*;

public class VinculoDAO {

    public void listarVinculos() {

        String sql =
            "SELECT * FROM universidade.vinculo";

        try (
            Connection conn = Conexao.conectar();
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(sql)
        ) {

            while (rs.next()) {

                System.out.println(
                    rs.getInt("idvinculo")
                    + " | "
                    + rs.getString("mat_estudante")
                    + " | "
                    + rs.getInt("curso")
                    + " | "
                    + rs.getString("status")
                );
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void inserirVinculo(
        String matricula,
        int curso,
        String status
    ) {

        String sql =
            "INSERT INTO universidade.vinculo " +
            "(mat_estudante,curso,status) " +
            "VALUES (?,?,?)";

        try (
            Connection conn = Conexao.conectar();
            PreparedStatement ps =
                conn.prepareStatement(sql)
        ) {

            ps.setString(1, matricula);
            ps.setInt(2, curso);
            ps.setString(3, status);

            ps.executeUpdate();

            System.out.println("Vínculo inserido!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void atualizarStatus(
        int idVinculo,
        String novoStatus
    ) {

        String sql =
            "UPDATE universidade.vinculo " +
            "SET status = ? " +
            "WHERE idvinculo = ?";

        try (
            Connection conn = Conexao.conectar();
            PreparedStatement ps =
                conn.prepareStatement(sql)
        ) {

            ps.setString(1, novoStatus);
            ps.setInt(2, idVinculo);

            ps.executeUpdate();

            System.out.println("Vínculo atualizado!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void removerVinculo(int idVinculo) {

        String sql =
            "DELETE FROM universidade.vinculo " +
            "WHERE idvinculo = ?";

        try (
            Connection conn = Conexao.conectar();
            PreparedStatement ps =
                conn.prepareStatement(sql)
        ) {

            ps.setInt(1, idVinculo);

            ps.executeUpdate();

            System.out.println("Vínculo removido!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}