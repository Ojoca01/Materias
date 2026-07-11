import java.sql.*;

public class EstudanteDAO {

    public void listarEstudantes() {

        String sql =
            "SELECT * FROM universidade.estudante";

        try (
            Connection conn = Conexao.conectar();
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(sql)
        ) {

            while (rs.next()) {

                System.out.println(
                    rs.getString("mat_estudante")
                    + " | "
                    + rs.getString("cpf")
                    + " | MC="
                    + rs.getDouble("mc")
                    + " | Ano="
                    + rs.getInt("ano_ingresso")
                );
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void inserirEstudante(
            String matricula,
            String cpf,
            double mc,
            int anoIngresso) {

        String sql =
            "INSERT INTO universidade.estudante " +
            "(mat_estudante, cpf, mc, ano_ingresso) " +
            "VALUES (?, ?, ?, ?)";

        try (
            Connection conn = Conexao.conectar();
            PreparedStatement ps =
                conn.prepareStatement(sql)
        ) {

            ps.setString(1, matricula);
            ps.setLong(2, Long.parseLong(cpf));
            ps.setDouble(3, mc);
            ps.setInt(4, anoIngresso);

            ps.executeUpdate();

            System.out.println("Estudante inserido!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void atualizarMC(
            String matricula,
            double novoMC) {

        String sql =
            "UPDATE universidade.estudante " +
            "SET mc = ? " +
            "WHERE mat_estudante = ?";

        try (
            Connection conn = Conexao.conectar();
            PreparedStatement ps =
                conn.prepareStatement(sql)
        ) {

            ps.setDouble(1, novoMC);
            ps.setString(2, matricula);

            ps.executeUpdate();

            System.out.println("Estudante atualizado!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void removerEstudante(
            String matricula) {

        String sql =
            "DELETE FROM universidade.estudante " +
            "WHERE mat_estudante = ?";

        try (
            Connection conn = Conexao.conectar();
            PreparedStatement ps =
                conn.prepareStatement(sql)
        ) {

            ps.setString(1, matricula);

            ps.executeUpdate();

            System.out.println("Estudante removido!");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}