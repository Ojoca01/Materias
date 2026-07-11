import java.sql.*;

public class CursoDAO {

    public void listarCursos() {

        String sql = "SELECT * FROM universidade.curso";

        try (
            Connection conn = Conexao.conectar();
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(sql)
        ) {

            while (rs.next()) {

                System.out.println(
                    rs.getInt("idcurso")
                    + " | "
                    + rs.getString("nome")
                    + " | "
                    + rs.getString("grau")
                    + " | "
                    + rs.getString("turno")
                    + " | "
                    + rs.getString("campus")
                    + " | "
                    + rs.getString("nivel")
                );
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void inserirCurso(
        String nome,
        String grau,
        String turno,
        String campus,
        String nivel
    ) {

        String sql =
            "INSERT INTO universidade.curso " +
            "(nome,grau,turno,campus,nivel) " +
            "VALUES (?,?,?,?,?)";

        try (
            Connection conn = Conexao.conectar();
            PreparedStatement ps = conn.prepareStatement(sql)
        ) {

            ps.setString(1, nome);
            ps.setString(2, grau);
            ps.setString(3, turno);
            ps.setString(4, campus);
            ps.setString(5, nivel);

            ps.executeUpdate();

            System.out.println("Curso inserido!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void atualizarCampus(
        int idCurso,
        String novoCampus
    ) {

        String sql =
            "UPDATE universidade.curso " +
            "SET campus = ? " +
            "WHERE idcurso = ?";

        try (
            Connection conn = Conexao.conectar();
            PreparedStatement ps = conn.prepareStatement(sql)
        ) {

            ps.setString(1, novoCampus);
            ps.setInt(2, idCurso);

            ps.executeUpdate();

            System.out.println("Curso atualizado!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void removerCurso(int idCurso) {

        String sql =
            "DELETE FROM universidade.curso " +
            "WHERE idcurso = ?";

        try (
            Connection conn = Conexao.conectar();
            PreparedStatement ps = conn.prepareStatement(sql)
        ) {

            ps.setInt(1, idCurso);

            ps.executeUpdate();

            System.out.println("Curso removido!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}