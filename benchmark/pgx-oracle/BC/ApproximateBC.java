/*
This class is written following the format in the Oracle PGX core demo
*/
import static oracle.pgx.api.algorithms.Argument.createGraphArg;

import java.util.List;
import java.util.Map;

import oracle.pgx.api.Core;
import oracle.pgx.api.InvocationResult;
import oracle.pgx.api.LoadingResult;
import oracle.pgx.api.admin.Control;
import oracle.pgx.api.admin.Pgx;
import oracle.pgx.api.algorithms.Argument;
import oracle.pgx.api.algorithms.BuiltinAlgorithms;
import oracle.pgx.api.analyst.PropertyProxy;
import oracle.pgx.api.config.GraphConfig;
import oracle.pgx.common.Types.PropertyType;

public class ApproximateBC {

  public static void main(String[] argv) throws Exception {

    if (argv.length != 2) {
      System.err.println("usage: " + ApproximateBC.class.getName() + " <graph config path>"
                          + " <number of random selected seed nodes to use> ");
      System.exit(-1);
    }
    GraphConfig cfg = GraphConfig.fromPath(argv[0]);

    String sessionId = null;
    Core core = null;
    try {
      core = Pgx.getCore();
      sessionId = core.createSession("my-session").get();
      LoadingResult graph = core.loadGraphWithProperties(sessionId, cfg).get();
      String graphName = graph.getGraphName();

      {
        String BCName = core.createNodeProperty(sessionId, graphName, PropertyType.DOUBLE).get();
        String ApproxBC = BuiltinAlgorithms.Type.PGX_BUILTIN_K3b_APPROX_NODE_BETWEENNESS_CENTRALITY.getAnalysisName();
        Argument[] args = new Argument[] {
          Argument.createGraphArg(graphName), 
          Argument.createIntArg(Integer.parseInt(argv[1])),
          Argument.createNodePropertyArg(BCName)
        };

        InvocationResult<Void> ir = core.runAnalysis(sessionId, ApproxBC, args, Void.class).get();
        if (ir.isSuccess()) {
          System.out.println("Approximate BC computed in " + ir.getExecutionTimeMs() + " milliseconds");
        } else {
          ir.getException().printStackTrace();
        }
        // uncomment the following and adjust accordingly if you want to see the result
        // make sure the getNodePropertyValue is called on an existing node
        /*
        PropertyProxy<Double> bc = core.<Double>getNodePropertyProxy(sessionId, graphName, BCName).get();
        double value = (Double) core.getNodePropertyValue(sessionId, graphName, BCName, 1).get();
        System.out.println("getNodePropertyValue(1) = " + value);
        Iterable<Map.Entry<Object, Double>> top3 = bc.getTopKValues(3);
        System.out.println("top3 = " + top3);
        */
      }

    } finally {

      Control ctrl = Pgx.getControl();
      if (ctrl.isRunning()) {
        if (sessionId != null) {
          core.destroySession(sessionId).get();
        }
        ctrl.shutdownNow();
      }
    }
  }

}
