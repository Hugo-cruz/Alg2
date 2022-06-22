import java.util.*;

public class DepthFirstSearch {


    Digraph_Matrix graph;
    LinkedList<Integer> visited;
    Queue<Integer> itensToVisit;
    ArrayList<Vertex> vertexList;

    public DepthFirstSearch(Digraph_Matrix graph, ArrayList vertexList) {
        this.graph = graph;
        visited = new LinkedList<>();
        itensToVisit = new LinkedList<>();
        this.vertexList = vertexList;

    }

    public boolean wasNotVisited(Integer nodeIndex){
        return visited.indexOf(nodeIndex) == -1;
    }

    public void visit(Integer nodeIndex) {

        if(wasNotVisited(nodeIndex)){
            visited.add(nodeIndex);
            System.out.println(vertexList.get(nodeIndex));
            int edge = 0;
            Integer nextVertex = graph.getNextConnectedVertexIndex(nodeIndex,edge);
            while(nextVertex != -1){
                if(wasNotVisited(nextVertex)){
                    itensToVisit.add(nextVertex);
                }
                edge++;
                nextVertex = graph.getNextConnectedVertexIndex(nodeIndex,edge);
            }
            //Integer nextItemToVisit = itensToVisit.pop();
        }


        return;
    }

    public void executeDFS(Integer initalVertex) {

        Integer nextVertex = initalVertex;
        do{
            visit(nextVertex);
            nextVertex = itensToVisit.remove();
        }while (!itensToVisit.isEmpty());
    }
}
