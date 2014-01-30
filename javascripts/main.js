var app = angular.module('gbApp', ["ngRoute"]);

app.controller('MainCntl', function($scope, $route, $routeParams, $location) {
  $scope.$route = $route;
  $scope.$location = $location;
  $scope.$routeParams = $routeParams;
});

app.config(function ($routeProvider) {
  $routeProvider
    .when('/intro',
    {
      templateUrl: "contents/intro.html",
      controller: "RouteCntl"
    }
  )
  $routeProvider.otherwise({redirectTo: '/intro'});
});

function MainCntl($scope, $route, $routeParams, $location) {
  $scope.$route = $route;
  $scope.$location = $location;
  $scope.$routeParams = $routeParams;
}

function RouteCntl($scope, $routeParams) {
}