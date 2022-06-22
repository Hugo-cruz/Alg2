import java.util.ArrayList;
import java.util.Scanner;

public class GraphController
{

    public static void main(String[] args)
    {
        ArrayList vertexList = new ArrayList();

        Scanner scan = new Scanner(System.in);
        String Nv = scan.nextLine();

        for(int i = 0;i<Integer.parseInt(Nv);i++){
            String questName = scan.nextLine();
            String questDescription = scan.nextLine();
            Vertex vertex = new Vertex(questName,questDescription,i);
            vertexList.add(vertex);
        }

        Digraph_Matrix g = new Digraph_Matrix(vertexList);

        String Na = scan.nextLine();

        for(int i = 0;i<Integer.parseInt(Na);i++){
            Integer origin = scan.nextInt();
            Integer destiny = scan.nextInt();
            g.addEdge(origin, destiny);
        }

        Integer initialVertex = scan.nextInt();
        System.out.println("Initial vertex: " + initialVertex);
        DepthFirstSearch DFS = new DepthFirstSearch(g,vertexList);
        DFS.executeDFS(Integer.valueOf(initialVertex));

        //g.printInGraphViz("Graph");

    }
}
