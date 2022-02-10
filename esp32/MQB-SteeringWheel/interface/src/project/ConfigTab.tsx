import MqbStatus from './StatusTab/MqbStatus'
import React, { FC } from 'react';
import { Navigate, Route, Routes } from 'react-router-dom';

import { Tab } from '@mui/material';

import { RouterTabs, useRouterTab, useLayoutTitle } from '../components';

import Config from "./ConfigTab/Config";

const ConfigTab: FC = () => {
  useLayoutTitle("Demo Project");
  const { routerTab } = useRouterTab();

  return (
    <>
      <RouterTabs value={routerTab}>
        <Tab value="config" label="Config" />
      </RouterTabs>
      <Routes>
        <Route path="config" element={<Config />} />
        <Route path="/*" element={<Navigate replace to="config" />} />
      </Routes>
    </>
  );
};

export default ConfigTab;


