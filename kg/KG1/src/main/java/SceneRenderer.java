import org.apache.commons.io.IOUtils;
import org.joml.Matrix4f;
import org.joml.Vector3f;
import org.lwjgl.BufferUtils;

import java.nio.FloatBuffer;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL15.*;
import static org.lwjgl.opengl.GL20.*;
import static org.lwjgl.opengl.GL30.glBindVertexArray;
import static org.lwjgl.opengl.GL30.glGenVertexArrays;

public class SceneRenderer {
    static final int vertexLocation = 0;
    static final int normalLocation = 1;

    public Vector3f modelPosition = new Vector3f(0, 0, 0);
    public Vector3f cameraPosition = new Vector3f(5, 1, 5);
    public Vector3f lightPosition = new Vector3f(0, 0, 2);
    public Vector3f modelRotation = new Vector3f(0, 0, 0);
    public Vector3f modelRotationSpeed = new Vector3f(0.025f, 0.025f, 0.025f);


    FloatBuffer pMatrix = BufferUtils.createFloatBuffer(16);
    FloatBuffer lightPoint = BufferUtils.createFloatBuffer(3);

    {
        new Matrix4f().perspective((float) Math.toRadians(45.0f), 640f / 480f, 0.01f, 100.0f)
                .get(pMatrix);
        System.out.println(pMatrix.get(0));
        System.out.println(pMatrix.get(1));
        System.out.println(pMatrix.get(2));
        System.out.println(pMatrix.get(3));
        System.out.println(pMatrix.get(4));
        System.out.println(pMatrix.get(5));
        System.out.println(pMatrix.get(6));
        System.out.println(pMatrix.get(7));
        System.out.println(pMatrix.get(8));
        System.out.println(pMatrix.get(9));
        System.out.println(pMatrix.get(10));
        System.out.println(pMatrix.get(11));
        System.out.println(pMatrix.get(12));
        System.out.println(pMatrix.get(13));
        System.out.println(pMatrix.get(14));
        System.out.println(pMatrix.get(15));
    }


    String vertexSource = IOUtils.toString(getClass().getResourceAsStream("shader.vert"), "UTF-8");
    String fragmentSource = IOUtils.toString(getClass().getResourceAsStream("shader.frag"), "UTF-8");

    String simpleVertexSource = IOUtils.toString(getClass().getResourceAsStream("simple.vert"), "UTF-8");
    String simpleFragmentSource = IOUtils.toString(getClass().getResourceAsStream("simple.frag"), "UTF-8");

    final int vertexBuffer;
    final int normalBuffer;
    final int axisBuffer;
    final int pointsBuffer;
    final int vaoLines;
    final int vaoPoints;
    final int vaoTriangles;
    final int shaderProgram;
    final int simpleProgram;


    public SceneRenderer() throws Exception {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glPointSize(10);

        shaderProgram = Util.createShaderProgram(vertexSource, fragmentSource);
        simpleProgram = Util.createShaderProgram(simpleVertexSource, simpleFragmentSource);

        vertexBuffer = glGenBuffers();
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, Geometry.cubeMesh, GL_STATIC_DRAW);



        normalBuffer = glGenBuffers();
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, Geometry.cubeNormal, GL_STATIC_DRAW);


        vaoTriangles = glGenVertexArrays();
        glBindVertexArray(vaoTriangles);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, false, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glVertexAttribPointer(normalLocation, 3, GL_FLOAT, false, 0, 0);

        axisBuffer = glGenBuffers();
        glBindBuffer(GL_ARRAY_BUFFER, axisBuffer);
        glBufferData(GL_ARRAY_BUFFER, Geometry.axis, GL_STATIC_DRAW);

        vaoLines = glGenVertexArrays();
        glBindVertexArray(vaoLines);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

        pointsBuffer = glGenBuffers();
        vaoPoints = glGenVertexArrays();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void render() throws Exception {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the framebuffer

        FloatBuffer vMatrix = BufferUtils.createFloatBuffer(16);
        new Matrix4f()
                .lookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
                        0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f).get(vMatrix);

        FloatBuffer mMatrix = BufferUtils.createFloatBuffer(16);
        new Matrix4f().translate(modelPosition)
                .rotateX(modelRotation.x)
                .rotateY(modelRotation.y)
                .rotateZ(modelRotation.z)
                .get(mMatrix);

        glUseProgram(simpleProgram);
        glUniformMatrix4fv(glGetUniformLocation(simpleProgram, "P"), false, pMatrix);
        glUniformMatrix4fv(glGetUniformLocation(simpleProgram, "V"), false, vMatrix);

        glBindVertexArray(vaoLines);
        glEnableVertexAttribArray(0);
        glUniform3f(glGetUniformLocation(simpleProgram, "c"), 1, 0, 0);
        glDrawArrays(GL_LINES, 0, 2);
        glUniform3f(glGetUniformLocation(simpleProgram, "c"), 0, 1, 0);
        glDrawArrays(GL_LINES, 2, 2);
        glUniform3f(glGetUniformLocation(simpleProgram, "c"), 0, 0, 1);
        glDrawArrays(GL_LINES, 4, 2);


        lightPosition.get(lightPoint);
        glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
        glBufferData(GL_ARRAY_BUFFER, lightPoint, GL_STATIC_DRAW);
        glBindVertexArray(vaoPoints);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_POINTS, 0, 1);

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "P"), false, pMatrix);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "V"), false, vMatrix);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "M"), false, mMatrix);
        glUniform3f(glGetUniformLocation(shaderProgram, "light_worldspace"), lightPosition.x, lightPosition.y, lightPosition.z);

        glBindVertexArray(vaoTriangles);

        glEnableVertexAttribArray(vertexLocation);
        glEnableVertexAttribArray(normalLocation);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
