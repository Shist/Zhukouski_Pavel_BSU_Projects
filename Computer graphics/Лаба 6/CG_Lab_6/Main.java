package lab_6;

import java.util.Arrays;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.scene.Group;
import javafx.scene.PerspectiveCamera;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.ScrollEvent;
import javafx.scene.paint.Color;
import javafx.scene.paint.PhongMaterial;
import javafx.scene.shape.DrawMode;
import javafx.scene.shape.MeshView;
import javafx.scene.shape.TriangleMesh;
import javafx.scene.transform.Rotate;
import javafx.stage.Stage;
import javafx.scene.shape.Box;
import javafx.scene.text.Font;
import javafx.stage.WindowEvent;
import threedimensionalobjects.TransformationInput;

import static lab_6.MatrixOper.multiplyVectorMatrix;

public class Main extends Application {

    private Group letterSystem = new Group();

    private boolean mouseClicked = false;
    
    private Rotate rX, rY, rZ;
    
    private final int height = 300;
    private final int width = 100;
    private final float[] initialPoints = { 
                0, 0, 0,
                0, 0, width,
                width, 0, width,
                width, 0, 0,
                0, -height, 0,
                0, -height, width,
                width, -height + width, width,
                width, -height + width, 0,
                2 * width, -height + width, 0,
                2 * width, -height + width, width,
                2 * width, 0, width,
                2 * width, 0, 0,
                3 * width, 0, 0,
                3 * width, 0, width,
                3 * width, -height, width,
                3 * width, -height, 0
    };
    
    private float[] points = Arrays.copyOf(initialPoints, initialPoints.length);
    
    private MeshView xyProjection, xzProjection, yzProjection, letterView;
    private final int[] faces = 
    {
                5, 0, 1, 0, 2, 0,
                2, 0, 1, 0, 5, 0,
                2, 0, 6, 0, 5, 0,
                5, 0, 6, 0, 2, 0,
                5, 0, 6, 0, 14, 0,
                14, 0, 6, 0, 5, 0,
                14, 0, 6, 0, 9, 0,
                9, 0, 6, 0, 14, 0,
                14, 0, 9, 0, 13, 0,
                13, 0, 9, 0, 14, 0,
                9, 0, 10, 0, 13, 0,
                13, 0, 10, 0, 9, 0,
                11, 0, 12, 0, 13, 0,
                13, 0, 12, 0, 11, 0,
                13, 0, 10, 0, 11, 0,
                11, 0, 10, 0, 13, 0,
                12, 0, 14, 0, 13, 0,
                13, 0, 14, 0, 12, 0,
                12, 0, 15, 0, 14, 0,
                14, 0, 15, 0, 12, 0,
                15, 0, 11, 0, 12, 0,
                12, 0, 11, 0, 15, 0,
                15, 0, 8, 0, 11, 0,
                11, 0, 8, 0, 15, 0,
                15, 0, 7, 0, 8, 0,
                8, 0, 7, 0, 15, 0,
                15, 0, 4, 0, 7, 0,
                7, 0, 4, 0, 15, 0,
                4, 0, 3, 0, 7, 0,
                7, 0, 3, 0, 4, 0,
                4, 0, 0, 0, 3, 0,
                3, 0, 0, 0, 4, 0,
                14, 0, 4, 0, 15, 0,
                14, 0, 5, 0, 4, 0,
                0, 0, 5, 0, 4, 0,
                4, 0, 5, 0, 0, 0,
                0, 0, 1, 0, 5, 0,
                5, 0, 1, 0, 0, 0,
                1, 0, 0, 0, 2, 0,
                2, 0, 0, 0, 1, 0,
                0, 0, 3, 0, 2, 0,
                2, 0, 3, 0, 0, 0,
                6, 0, 7, 0, 3, 0,
                3, 0, 7, 0, 6, 0,
                6, 0, 3, 0, 2, 0,
                2, 0, 3, 0, 6, 0,
                9, 0, 8, 0, 11, 0,
                2, 0, 3, 0, 0, 0,
                3, 0, 7, 0, 6, 0,
                11, 0, 8, 0, 9, 0,
                9, 0, 8, 0, 11, 0,
                9, 0, 10, 0, 11, 0,
                11, 0, 10, 0, 9, 0,
                7, 0, 6, 0, 9, 0,
                7, 0, 9, 0, 8, 0  
    };
    private TriangleMesh letterMesh;
    
    private Font font = new Font("System", 25);
    
    private void buildLetter() {
        letterMesh = new TriangleMesh();
        
        letterMesh.getPoints().addAll(initialPoints);
        letterMesh.getTexCoords().addAll(0, 0);
        letterMesh.getFaces().addAll(faces);

        letterView = new MeshView(letterMesh);
        letterView.setDrawMode(DrawMode.LINE);
        letterView.setMaterial(new PhongMaterial(Color.MAGENTA));
        letterSystem.getChildren().add(letterView);
    }

    private void buildAxesAndGrid() {
        double thickness = 2;
        int length = 400;
        int fullLength = length * 2;
        
        Box xAxis = createBox(fullLength, thickness, thickness, Color.CORAL);
        Box yAxis = createBox(thickness, fullLength, thickness, Color.LIME);
        Box zAxis = createBox(thickness, thickness, fullLength, Color.AQUA);
        letterSystem.getChildren().addAll(xAxis, yAxis, zAxis);
         
        Label labelX = new Label("x");
        labelX.setFont(font);
        labelX.setTranslateX(length);  
        labelX.setTranslateY(5*thickness);  
        Label labelY = new Label("y");
        labelY.setFont(font);
        labelY.setTranslateY(length);
        labelY.setTranslateX(15 * thickness);
        Label labelZ = new Label("z");
        labelZ.setFont(font);
        labelZ.setTranslateZ(length);
        labelZ.setTranslateX(5 * thickness);
        labelZ.setTranslateY(5 * thickness);
        
        letterSystem.getChildren().addAll(labelX, labelY, labelZ);

        font = new Font("System", 18);
        thickness = 0.3;
        int n = fullLength / 100;
        Label[] labelsX = new Label[n + 1];
        Label[] labelsY = new Label[n + 1];
        Label[] labelsZ = new Label[n + 1];
        for (int i = -n / 2; i <= n / 2; i++) {
            int translate = i * 100;
            
            Box x = createBox(fullLength, thickness, thickness, Color.BLUE);
            x.setTranslateZ(translate);
            x.setTranslateY(translate);
            labelsX[i + n/2] = new Label(Integer.toString(translate));
            labelsX[i + n/2].setFont(font);
            labelsX[i + n/2].setTranslateX(translate);
            
            Box y = createBox(thickness, fullLength, thickness, Color.BLUE);
            y.setTranslateZ(translate);
            y.setTranslateX(translate);
            labelsY[i + n/2] = new Label(Integer.toString(translate));
            labelsY[i + n/2].setFont(font);
            labelsY[i + n/2].setTranslateY(translate);
            
            Box z = createBox(thickness, thickness, fullLength, Color.BLUE);
            z.setTranslateX(translate);
            z.setTranslateY(translate);
            labelsZ[i + n/2] = new Label(Integer.toString(translate));
            labelsZ[i + n/2].setFont(font);
            labelsZ[i + n/2].setTranslateZ(translate);
            
            letterSystem.getChildren().addAll(x, labelsX[i + n / 2], y, labelsY[i + n / 2], z, labelsZ[i + n / 2]);
        }
    }
    private void initTransforms(){
        rX = new Rotate(0, Rotate.X_AXIS);
        rY = new Rotate(0, Rotate.Y_AXIS);
        rZ = new Rotate(0, Rotate.Z_AXIS);
        rX.setAngle(20);
        rY.setAngle(15);
        
        letterSystem.getTransforms().addAll(rX, rY, rZ);
        letterSystem.setLayoutX(-350);
        letterSystem.setLayoutY(400);
    }
     
    private Box createBox(double w, double h, double d, Color color)
    {
        Box box = new Box(w, h, d);
        box.setMaterial(new PhongMaterial(color));
        return box;
    }


    private Button createButton(String title, int y)
    {
        Button button = new Button();
        button.setText(title);
        button.setFont(font);
        button.setLayoutX(200);
        button.setLayoutY(y);
        return button;
    }
    
    private void loadInputWindow(Stage stage){
        TransformationInput input = new TransformationInput();
        try {
            Stage childStage = new Stage();
            childStage.getProperties().put("letter", letterView);
            childStage.getProperties().put("initialPoints", initialPoints);
            childStage.getProperties().put("points", points);
            stage.setOnCloseRequest((WindowEvent we) -> {
                letterSystem.setTranslateX(200);
            });
            childStage.initOwner(stage);
            input.start(childStage);
        } 
        catch (Exception ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
        
    private void addButtonsToStage(Stage stage, Group root){
        Button transformateButton = createButton("Преобразовать", 500);
      transformateButton.setStyle("-fx-background-color: #FF2819;");
        transformateButton.setOnAction((final ActionEvent e) -> {
            loadInputWindow(stage);
        });
        Button xyButton = createButton("Oxy проекция", 100);
        xyButton.setStyle("-fx-background-color: #15FF00;");
        xyButton.setOnAction((final ActionEvent e) -> {
            if(xyProjection == null){
                buildProjection(1, 1, 0, Color.LIME, 1);
            }
            else {
                letterSystem.getChildren().remove(xyProjection);
                xyProjection = null;
            }
        });
        Button xzButton = createButton("Oxz проекция", 150);
        
        xzButton.setStyle("-fx-background-color: #15FF00;");
        xzButton.setOnAction((final ActionEvent e) -> 
        {
            if (xzProjection == null) {
                buildProjection(1, 0, 1, Color.DEEPPINK, 2);
            } 
            else {
                letterSystem.getChildren().remove(xzProjection);
                xzProjection = null;
            }
        });
        Button yzButton = createButton("Oyz проекция", 200);
        yzButton.setStyle("-fx-background-color: #15FF00;");
        yzButton.setOnAction((final ActionEvent e) -> {
            if (yzProjection == null) {
                buildProjection(0, 1, 1, Color.CHOCOLATE, 3);
            } 
            else {
                letterSystem.getChildren().remove(yzProjection);
                yzProjection = null;
            }
        });
        root.getChildren().addAll(transformateButton, xyButton, xzButton, yzButton);
    }
    private PerspectiveCamera createCamera(){
        PerspectiveCamera camera = new PerspectiveCamera(false);
        camera.setTranslateX(-600);
        camera.setTranslateY(100); 
        camera.setTranslateZ(-600);
        return camera;
    }
    
    private void buildProjection(int x, int y, int z, Color color, int projection){
        float[][] translate = {
            {x, 0, 0},
            {0, y, 0},
            {0, 0, z}
        };
    
        float[] projectionPoints = new float[points.length];
        
        for(int i = 0; i < points.length; i += 3){
            System.arraycopy(multiplyVectorMatrix(translate, Arrays.copyOfRange(points, i, i + 3)), 0, projectionPoints, i, 3);
        }
      
        TriangleMesh projectionMesh = new TriangleMesh();
        
        projectionMesh.getPoints().addAll(projectionPoints);
        projectionMesh.getTexCoords().addAll(0, 0);
        projectionMesh.getFaces().addAll(faces);
        
        switch (projection) {
            case 1:
                xyProjection = new MeshView(projectionMesh);
                xyProjection.setMaterial(new PhongMaterial(color));
                letterSystem.getChildren().add(xyProjection);
                break;
            case 2:
                xzProjection = new MeshView(projectionMesh);
                xzProjection.setMaterial(new PhongMaterial(color));
                letterSystem.getChildren().add(xzProjection);
                break;
            case 3:
                yzProjection = new MeshView(projectionMesh);
                yzProjection.setMaterial(new PhongMaterial(color));
                letterSystem.getChildren().add(yzProjection);
                break;
        }
    }
    
    private void initSceneActions(Scene scene){
        PerspectiveCamera camera = createCamera();
        scene.setCamera(camera);  
        
        scene.setOnMouseClicked((final MouseEvent e) -> {
            if (e.getX() < -45) {
                mouseClicked = !mouseClicked;
            }
        });
        scene.setOnMouseMoved((final MouseEvent e) -> {
            if (mouseClicked) {
                if (e.isShiftDown()) {
                    rZ.setAngle(e.getSceneX() * 360 / scene.getWidth());
                } else {
                    rX.setAngle(e.getSceneY() * 360 / scene.getHeight());
                    rY.setAngle(e.getSceneX() * 360 / scene.getWidth());
                }
            }
        });
        scene.setOnScroll((final ScrollEvent e) -> {
            camera.setTranslateZ(camera.getTranslateZ() + e.getDeltaY());
        });

    }
    
    @Override
    public void start(Stage stage) throws Exception {
        letterSystem = new Group();

        buildLetter();
        buildAxesAndGrid();
        initTransforms();
        
        Group root = new Group(letterSystem);
        addButtonsToStage(stage, root);
   
        Scene scene = new Scene(root, 1000, 800, true);
        initSceneActions(scene);
      
        stage.setScene(scene);
        stage.setTitle("Построение и визуализация трехмерных объектов. ");
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}