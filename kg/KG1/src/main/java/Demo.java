import org.joml.Vector3f;
import org.lwjgl.glfw.GLFW;
import org.lwjgl.glfw.GLFWErrorCallback;

import static org.lwjgl.glfw.GLFW.*;

public class Demo {
    enum WHAT_MOVE {
        MODEL, CAMERA, LIGHT
    }

    static class ControlState {
        WHAT_MOVE whatMove = WHAT_MOVE.MODEL;
    }

    public static void main(String[] args) throws Exception {
        GLFWErrorCallback.createPrint(System.err).set();

        if (glfwInit() == false)
            throw new IllegalStateException("Unable to initialize GLFW");

        Window wnd = new Window(640, 480, "LWJGL - Shaders - Bullet!");
        SceneRenderer render = new SceneRenderer();
        ControlState cs = new ControlState();

        wnd.setKeyListener((key, scancode, action) -> {
            switch (key) {
                case GLFW_KEY_1:
                    System.out.println("move model");
                    cs.whatMove = WHAT_MOVE.MODEL;
                    break;
                case GLFW_KEY_2:
                    System.out.println("move camera");
                    cs.whatMove = WHAT_MOVE.CAMERA;
                    break;
                case GLFW_KEY_3:
                    System.out.println("move light");
                    cs.whatMove = WHAT_MOVE.LIGHT;
                    break;
            }

            Vector3f whatToMove = null;
            switch (cs.whatMove) {
                case MODEL:
                    whatToMove = render.modelPosition;
                    break;
                case CAMERA:
                    whatToMove = render.cameraPosition;
                    break;
                case LIGHT:
                    whatToMove = render.lightPosition;
                    break;
            }

            float step = 0.1f;

            switch (key) {
                case GLFW_KEY_W:
                    whatToMove.add(0, step, 0);
                    break;
                case GLFW_KEY_S:
                    whatToMove.sub(0, step, 0);
                    break;
                case GLFW_KEY_A:
                    whatToMove.sub(step, 0, 0);
                    break;
                case GLFW_KEY_D:
                    whatToMove.add(step, 0, 0);
                    break;
                case GLFW_KEY_Q:
                    whatToMove.sub(0, 0, step);
                    break;
                case GLFW_KEY_E:
                    whatToMove.add(0, 0, step);
                    break;
            }

        }).render(() -> {
            render.modelRotation.add(render.modelRotationSpeed);
            render.render();
        });

        glfwTerminate();
    }
}