import { FC } from 'react';
import { Navigate, Routes, Route } from 'react-router-dom';

import DemoProject from './DemoProject';
import StatusTab from './StatusTab';
import ConfigTab from "./ConfigTab";
import DebugTab from "./DebugTab";

const ProjectRouting: FC = () => {
  return (
    <Routes>
      {
        // Add the default route for your project below
      }
      <Route path="/*" element={<Navigate to="demo/information" />} />
      {
        // Add your project page routes below.
      }
      <Route path="demo/*" element={<DemoProject />} />
      <Route path="status/*" element={<StatusTab />} />
      <Route path="config/*" element={<ConfigTab />} />
      <Route path="debug/*" element={<DebugTab />} />
    </Routes>
  );
};

export default ProjectRouting;
