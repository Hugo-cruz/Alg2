public class Vertex
{
    String name;
    String description;
    Integer id;

    public Vertex(String name, String description, Integer id) {
        this.name = name;
        this.description = description;
        this.id = id;
    }

    public Vertex(String name, String description) {
        this.name = name;
        this.description = description;
    }

    @Override
    public String toString() {
        return "Quest{" +
                "ID=" + id +
                "name='" + name + '\'' +
                "description='" + description + '\'' +

                '}';
    }
}
