import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        UsuarioDAO usuarioDAO = new UsuarioDAO();
        CursoDAO cursoDAO = new CursoDAO();
        EstudanteDAO estudanteDAO = new EstudanteDAO();
        VinculoDAO vinculoDAO = new VinculoDAO();

        int opcao = -1;

        while (opcao != 0) {

            System.out.println("\n==============================");
            System.out.println("       CRUD UNIVERSIDADE");
            System.out.println("==============================");

            System.out.println("\nTABELA USUÁRIOS");
            System.out.println("1  - Listar Usuários");
            System.out.println("2  - Inserir Usuário");
            System.out.println("3  - Atualizar Email Usuário");
            System.out.println("4  - Remover Usuário");


            System.out.println("\nTABELA CURSOS");
            System.out.println("5  - Listar Cursos");
            System.out.println("6  - Inserir Curso");
            System.out.println("7  - Atualizar Campus Curso");
            System.out.println("8  - Remover Curso");


            System.out.println("\nTABELA ESTUDANTES");
            System.out.println("9  - Listar Estudantes");
            System.out.println("10 - Inserir Estudante");
            System.out.println("11 - Atualizar MC");
            System.out.println("12 - Remover Estudante");


            System.out.println("\nTABELA VÍNCULOS");
            System.out.println("13 - Listar Vínculos");
            System.out.println("14 - Inserir Vínculo");
            System.out.println("15 - Atualizar Status Vínculo");
            System.out.println("16 - Remover Vínculo");


            System.out.println("\n0 - Sair");

            System.out.print("\nOpção: ");


            try {

                opcao = Integer.parseInt(sc.nextLine());


                switch (opcao) {


                    // =========================
                    // USUÁRIO
                    // =========================

                    case 1:

                        usuarioDAO.listarUsuarios();

                        break;


                    case 2:

                        System.out.print("CPF: ");
                        String cpf = sc.nextLine();


                        System.out.print("Nome: ");
                        String nome = sc.nextLine();


                        System.out.print("Data nascimento (AAAA-MM-DD): ");

                        SimpleDateFormat sdf =
                                new SimpleDateFormat("yyyy-MM-dd");

                        Date nascimento =
                                sdf.parse(sc.nextLine());


                        System.out.print("Email: ");
                        String email = sc.nextLine();


                        System.out.print("Telefone: ");
                        String telefone = sc.nextLine();


                        System.out.print("Login: ");
                        String login = sc.nextLine();


                        System.out.print("Senha: ");
                        String senha = sc.nextLine();


                        usuarioDAO.inserirUsuario(
                                cpf,
                                nome,
                                nascimento,
                                email,
                                telefone,
                                login,
                                senha
                        );


                        break;


                    case 3:

                        System.out.print("CPF: ");
                        cpf = sc.nextLine();


                        System.out.print("Novo email: ");
                        email = sc.nextLine();


                        usuarioDAO.atualizarEmail(
                                cpf,
                                email
                        );


                        break;


                    case 4:

                        System.out.print("CPF: ");
                        cpf = sc.nextLine();


                        usuarioDAO.removerUsuario(cpf);


                        break;



                    // =========================
                    // CURSO
                    // =========================

                    case 5:

                        cursoDAO.listarCursos();

                        break;


                    case 6:

                        System.out.print("Nome: ");
                        String nomeCurso = sc.nextLine();


                        System.out.print("Grau: ");
                        String grau = sc.nextLine();


                        System.out.print("Turno: ");
                        String turno = sc.nextLine();


                        System.out.print("Campus: ");
                        String campus = sc.nextLine();


                        System.out.print("Nível: ");
                        String nivel = sc.nextLine();


                        cursoDAO.inserirCurso(
                                nomeCurso,
                                grau,
                                turno,
                                campus,
                                nivel
                        );


                        break;


                    case 7:

                        System.out.print("ID Curso: ");

                        int idCurso =
                                Integer.parseInt(sc.nextLine());


                        System.out.print("Novo Campus: ");

                        campus = sc.nextLine();


                        cursoDAO.atualizarCampus(
                                idCurso,
                                campus
                        );


                        break;



                    case 8:

                        System.out.print("ID Curso: ");

                        idCurso =
                                Integer.parseInt(sc.nextLine());


                        cursoDAO.removerCurso(idCurso);


                        break;



                    // =========================
                    // ESTUDANTE
                    // =========================

                    case 9:

                        estudanteDAO.listarEstudantes();

                        break;



                    case 10:

                        System.out.print("Matrícula: ");
                        String matricula =
                                sc.nextLine();


                        System.out.print("CPF: ");
                        cpf =
                                sc.nextLine();


                        System.out.print("MC: ");

                        double mc =
                                Double.parseDouble(sc.nextLine());


                        System.out.print("Ano ingresso: ");

                        int ano =
                                Integer.parseInt(sc.nextLine());


                        estudanteDAO.inserirEstudante(
                                matricula,
                                cpf,
                                mc,
                                ano
                        );


                        break;



                    case 11:

                        System.out.print("Matrícula: ");

                        matricula =
                                sc.nextLine();


                        System.out.print("Novo MC: ");

                        mc =
                                Double.parseDouble(sc.nextLine());


                        estudanteDAO.atualizarMC(
                                matricula,
                                mc
                        );


                        break;



                    case 12:

                        System.out.print("Matrícula: ");

                        matricula =
                                sc.nextLine();


                        estudanteDAO.removerEstudante(
                                matricula
                        );


                        break;




                    // =========================
                    // VÍNCULO
                    // =========================


                    case 13:

                        vinculoDAO.listarVinculos();

                        break;



                    case 14:

                        System.out.print("Matrícula: ");

                        matricula =
                                sc.nextLine();


                        System.out.print("ID Curso: ");

                        int curso =
                                Integer.parseInt(sc.nextLine());


                        System.out.print("Status: ");

                        String status =
                                sc.nextLine();



                        vinculoDAO.inserirVinculo(
                                matricula,
                                curso,
                                status
                        );


                        break;



                    case 15:

                        System.out.print("ID Vínculo: ");

                        int idVinculo =
                                Integer.parseInt(sc.nextLine());


                        System.out.print("Novo Status: ");

                        status =
                                sc.nextLine();



                        vinculoDAO.atualizarStatus(
                                idVinculo,
                                status
                        );


                        break;



                    case 16:

                        System.out.print("ID Vínculo: ");

                        idVinculo =
                                Integer.parseInt(sc.nextLine());


                        vinculoDAO.removerVinculo(
                                idVinculo
                        );


                        break;



                    case 0:

                        System.out.println("\nEncerrando...");

                        break;



                    default:

                        System.out.println("Opção inválida.");

                }


            } catch (Exception e) {

                System.out.println(
                        "Erro: " + e.getMessage()
                );

            }


        }


        ConexaoMongo.fechar();

        sc.close();

    }

}